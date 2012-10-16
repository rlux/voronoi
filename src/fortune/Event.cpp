#include <fortune/Event.h>

using namespace voronoi;
using namespace voronoi::fortune;
using namespace geometry;

bool Event::isSiteEvent() const
{
	return false;
}

bool Event::isCircleEvent() const
{
	return false;
}

bool Event::operator<(const Event& event) const {
	Point p1 = position();
	Point p2 = event.position();
	
	return p1.y()==p2.y() ? p1.x()>p2.x() : p1.y()<p2.y();
}

SiteEvent* Event::asSiteEvent() const
{
	return isSiteEvent() ? (SiteEvent*)this : nullptr;
}

CircleEvent* Event::asCircleEvent() const
{
	return isCircleEvent() ? (CircleEvent*)this : nullptr;
}

SiteEvent::SiteEvent(VoronoiSite* site) : site(site)
{
}

bool SiteEvent::isSiteEvent() const
{
	return true;
}

Point SiteEvent::position() const
{
	return site->position();
}

CircleEvent::CircleEvent(Arc* arc, Circle circle) : valid(true), arc(arc), circle(circle)
{
	arc->invalidateEvent();
	arc->event = this;
}

bool CircleEvent::isCircleEvent() const
{
	return true;
}

Point CircleEvent::position() const
{
	return circle.center()-Point(0,circle.radius());
}

bool EventComparator::operator()(Event* event1, Event* event2) {
	return *event1 < *event2;
}
