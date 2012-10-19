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

#include <fortune/Arc.h>
#include <fortune/Event.h>
#include <fortune/BeachLine.h>
#include <cmath>

using namespace voronoi;
using namespace voronoi::fortune;
using namespace geometry;

Arc::Arc(BeachLine* beachLine, VoronoiSite* site) : beachLine(beachLine), _site(site)
{
	_prev = _next = 0;
	_event = 0;
	_leftEdge = 0;
}

Arc* Arc::prev() const
{
	return _prev;
}

Arc* Arc::next() const
{
	return _next;
}

VoronoiSite* Arc::site() const
{
	return _site;
}

VoronoiEdge* Arc::leftEdge() const
{
	return _leftEdge;
}

VoronoiEdge* Arc::rightEdge() const
{
	if (!_next) return 0;
	return _next->_leftEdge;
}

void Arc::setLeftEdge(VoronoiEdge* leftEdge)
{
	_leftEdge = leftEdge;
}

bool Arc::getTriangle(Triangle& triangle) const
{
	if (!_prev || !_next || _prev->_site == _next->_site) return false;
	
	triangle = Triangle(_prev->_site->position(), _next->_site->position(), _site->position());
	
	return true;
}

void Arc::invalidateEvent()
{
	if (!_event) return;
	_event->invalidate();
	_event = 0;
}

void Arc::resetEvent(CircleEvent* event)
{
	invalidateEvent();
	_event = event;
}

Point Arc::intersection(const Point& focus1, const Point& focus2, real baselineY, bool left, bool& intersects)
{	
	// parabola formula: (x-h)^2 = 4a(y-k) with vertex=(h,k) and a=dist(line, vertex)/2
	real h1 = focus1.x();
	real a1 = (focus1.y()-baselineY)/2;
	real k1 = focus1.y()-a1;
	
	real h2 = focus2.x();
	real a2 = (focus2.y()-baselineY)/2;
	real k2 = focus2.y()-a2;
		
	real x,y;

	if (a1==0 && a2==0) { // no intersection
		intersects = false;
		return Point();		
	}
	intersects = true;
	
	if (a1==a2) { // optimization
		x = (h1+h2)/2;
	} else if (a1==0) { // first parabola lies on baseline -> degenerates to line
		x = h1;
		y = (x-h2)*(x-h2)/(4*a2)+k2;
		return Point(x,y);
	} else if (a2==0) { // second parabola lies on baseline -> degenerates to line
		x = h2;
	} else {
		real p = 2*(h2*a1-h1*a2)/(a2-a1);
		real q = (4*a1*a2*(k1-k2)+h1*h1*a2-h2*h2*a1)/(a2-a1);
		real D = p*p/4-q;
		
		real sqrtD = sqrt(D);
		
		if (left) sqrtD = -sqrtD;
		x = -p/2+sqrtD;
	}
	
	y = (x-h1)*(x-h1)/(4*a1)+k1;
	
	return Point(x,y);
}

