/**
  * (C) LGPL-3
  *
  * Voronoi++ <https://github.com/rlux/voronoi>
  *
  * Copyright: 2012 Lux, Scheibel
  * Authors:
  *     Roland Lux <rollux2000@googlemail.com>
  *     Willy Scheibel <willyscheibel@gmx.de>
  * 
  * This file is part of Voronoi++.
  *
  * Voronoi++ is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Lesser General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  * 
  * Voronoi++ is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU Lesser General Public License for more details.
  * 
  * You should have received a copy of the GNU Lesser General Public License
  * along with Voronoi++.  If not, see <http://www.gnu.org/licenses/>.
  **/

#include <fortune/Fortune.h>

using namespace voronoi;
using namespace voronoi::fortune;
using namespace geometry;

Fortune::Fortune() : diagram(0), sweepLineY(0)
{
}

void Fortune::operator()(VoronoiDiagram* diagram)
{
	initialize(diagram);
	calculate();
	this->diagram = 0;
}

void Fortune::initialize(VoronoiDiagram* diagram)
{
	this->diagram = diagram;
	while (Event* event = nextEvent()) delete event;
	addEventsFor(diagram->sites());
}

real Fortune::getSweepLineY() const
{
	return sweepLineY;
}

bool Fortune::step()
{
	while (Event* event = nextEvent()) {
		bool wasCircle = event->isCircleEvent();
		processEvent(event);
		delete event;
		if (wasCircle) return true;
	}
	return false;
}

void Fortune::calculate()
{	
	while (Event* event = nextEvent()) {
		processEvent(event);
		delete event;
	}
}

void Fortune::processEvent(Event* event)
{
	sweepLineY = event->position().y();
	
	if (event->isSiteEvent()) {
		handleSiteEvent(event->asSiteEvent());
	} else {
		handleCircleEvent(event->asCircleEvent());
	}
}

void Fortune::addEventsFor(std::vector<VoronoiSite*>& sites)
{
	for (std::vector<VoronoiSite*>::iterator it = sites.begin(); it != sites.end(); ++it) {
		addEvent(new SiteEvent(*it));
	}
}

void Fortune::addEvent(Event* event)
{
	eventQueue.push(event);
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

void Fortune::handleSiteEvent(SiteEvent* event)
{
	VoronoiSite* site = event->site();
	
	Arc* newArc = beachLine.createArc(site);
	
	if (beachLine.isEmpty()) {
		beachLine.insert(newArc);
		return;
	}
	
	Arc* arc = beachLine.arcAbove(site->position());
	
	if (arc) {
		arc->invalidateCircleEvent();
		newArc->setLeftEdge(createEdgeBetween(arc->site(), site));
		
		beachLine.splitArcWith(arc, newArc);
		//arc->splitWith(newArc);
	} else {
		Arc* last = beachLine.lastElement();
		newArc->setLeftEdge(createEdgeBetween(last->site(), site));
		//last->insert(newArc);
		beachLine.insertAfter(newArc, last);
	}
	
	checkForCircleEvent(newArc->prev());
	checkForCircleEvent(newArc->next());
}
#include <iostream>
void Fortune::handleCircleEvent(CircleEvent* event)
{
	if (!event->isValid()) return;
	
	Arc* arc = event->arc();
	Arc* prev = arc->prev();
	Arc* next = arc->next();
	VoronoiEdge* leftEdge = arc->leftEdge();
	VoronoiEdge* rightEdge = arc->rightEdge();
	Point centerPoint = event->circle().center();
	
	VoronoiEdge* newEdge = createEdgeBetween(prev->site(), next->site());
	
	newEdge->adjustOrientation(arc->site()->position());
	newEdge->addPoint(centerPoint);
	
	leftEdge->adjustOrientation(next->site()->position());
	leftEdge->addPoint(centerPoint);
	
	rightEdge->adjustOrientation(prev->site()->position());
	rightEdge->addPoint(centerPoint);
	
	// connect half edges
	VoronoiHalfEdge* he = leftEdge->halfEdgeFor(arc->site());
	he->setStartPoint(centerPoint);
	he->setPrev(rightEdge->halfEdgeFor(arc->site()));
	
	he = rightEdge->halfEdgeFor(next->site());
	he->setStartPoint(centerPoint);
	he->setPrev(newEdge->halfEdgeFor(next->site()));
	
	he = newEdge->halfEdgeFor(prev->site());
	he->setStartPoint(centerPoint);
	he->setPrev(leftEdge->halfEdgeFor(prev->site()));
	
	
	beachLine.replaceArc(arc, newEdge);
	
	checkForCircleEvent(prev);
	checkForCircleEvent(next);
}
#include <iostream>
void Fortune::checkForCircleEvent(Arc* arc)
{
	if (!arc) return;
	arc->invalidateCircleEvent();
	
	if (!arc->hasTwoDifferentNeighborSites()) return;
	
	Point a = arc->prev()->site()->position();
	Point b = arc->next()->site()->position();
	Point c = arc->site()->position();
	
	if (pointsOnLine(a, b, c)) {
		if (a.x() >= b.x() && b.x() >= c.x()) {
			
		} else {
			return;
		}
	} else {
		if (clockwise(a, b, c)) return;
	}
	
	Circle circle(a, b, c);
	
	if (circle.top().y() > sweepLineY) {
		std::cout << "yes" << std::endl;
		//return;
	}

	addEvent(new CircleEvent(arc, circle));
}

VoronoiEdge* Fortune::createEdgeBetween(VoronoiSite* site1, VoronoiSite* site2)
{
	return diagram->createEdge(site1, site2);
}

