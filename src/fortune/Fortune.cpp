#include <fortune/Fortune.h>

#include <unordered_map>
#include <iostream>

#include <geometry/Triangle.h>

using namespace voronoi;
using namespace voronoi::fortune;
using namespace geometry;

Fortune::Fortune()
{
}

void Fortune::operator()(VoronoiDiagram& diagram)
{
	this->diagram = diagram;
	calculate();
}

void Fortune::calculate()
{
	sweepPos = 0;
	
	for (VoronoiSite& site: diagram.sites()) {
		addEvent(new SiteEvent(&site));
	}
	
	while (Event* event = nextEvent()) {
		sweepPos = event->position().y();
		if (event->isSiteEvent()) {
			handleSiteEvent(event->asSiteEvent());
		} else {
			handleCircleEvent(event->asCircleEvent());
		}
		delete event;
	}
}

void Fortune::handleSiteEvent(SiteEvent* event)
{
	VoronoiSite* site = event->site;
	
	if (!beachLine.firstElement) {
		beachLine.firstElement = new Arc(site);
		return;
	}
	
	Arc* arc = beachLine.arcFor(site->position());
	
	Arc* newArc = new Arc(site);
	
	if (arc) {
		arc->invalidateEvent();
		newArc->leftEdge = diagram.createEdge(arc->site, site);
		arc->splitWith(newArc);
	} else {
		Arc* last = beachLine.lastElement();
		newArc->leftEdge = diagram.createEdge(last->site, site);
		last->insert(newArc);
	}
	
	if (newArc->prev) checkCircleEvent(newArc->prev);
	if (newArc->next) checkCircleEvent(newArc->next);
}

void Fortune::handleCircleEvent(CircleEvent* event)
{
	if (!event->valid) return;
	
	Arc* arc = event->arc;
	Arc* prev = arc->prev;
	Arc* next = arc->next;
	VoronoiEdge* leftEdge = arc->leftEdge;
	VoronoiEdge* rightEdge = arc->rightEdge();
	Point s = event->circle.center();
	
	VoronoiEdge* newEdge = diagram.createEdge(prev->site, next->site);
	newEdge->adjustOrientation(arc->site->position());
	newEdge->addPoint(s);
	
	if (leftEdge) {
		leftEdge->adjustOrientation(next->site->position());
		leftEdge->addPoint(s);
	}
	if (rightEdge) {
		rightEdge->adjustOrientation(prev->site->position());
		rightEdge->addPoint(s);
	}
		
	beachLine.replaceArc(arc, newEdge);
	
	checkCircleEvent(prev);
	checkCircleEvent(next);
}

void Fortune::checkCircleEvent(Arc* arc)
{
	arc->invalidateEvent();
	
	Arc* prev = arc->prev;
	Arc* next = arc->next;
	
	if (!prev || !next || prev->site == next->site) return;
	
	Triangle triangle(prev->site->position(), next->site->position(), arc->site->position());
	if (triangle.isClockwise()) return;
	
	Circle circle = triangle.circumcircle();
	
	if (circle.center().y()-circle.radius() > sweepPos) {
		return;
	}

	addEvent(new CircleEvent(arc, circle));
}

Event* Fortune::nextEvent()
{
	if (eventQueue.empty()) {
		return 0;
	}
	
	Event* event = eventQueue.top();
	eventQueue.pop();
	
	return event;
}

void Fortune::addEvent(Event* event)
{
	eventQueue.push(event);
}

