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

Parabola Arc::parabola(real baselineY) const
{
	return Parabola(_site->position(), baselineY);
}

void Arc::setLeftEdge(VoronoiEdge* leftEdge)
{
	_leftEdge = leftEdge;
}

bool Arc::hasTwoDifferentNeighborSites() const
{
	return _prev && _next && _prev->_site != _next->_site;
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

