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
	return isSiteEvent() ? (SiteEvent*)this : 0;
}

CircleEvent* Event::asCircleEvent() const
{
	return isCircleEvent() ? (CircleEvent*)this : 0;
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
