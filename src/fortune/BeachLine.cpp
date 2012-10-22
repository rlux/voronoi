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

#include <fortune/BeachLine.h>
#include <stdexcept>

using namespace voronoi;
using namespace voronoi::fortune;
using namespace geometry;

BeachLine::BeachLine() : _firstElement(0), _lastElement(0)
{
}

Arc* BeachLine::createArc(VoronoiSite* site)
{
	return new Arc(this, site);
}

bool BeachLine::isEmpty() const
{
	return _firstElement==0;
}

void BeachLine::insert(Arc* arc)
{
	if (arc->beachLine != this) {
		throw std::runtime_error("Cannot insert arc from another beachline");
	}
	
	if (!_firstElement) {
		_firstElement = _lastElement = arc;
	} else {
		insertAfter(arc, _lastElement);
	}
}

void BeachLine::insertAfter(Arc* newArc, Arc* after)
{
	linkArcs(newArc, after->next());
	linkArcs(after, newArc);
	if (after==_lastElement) {
		_lastElement = newArc;
	}
}

void BeachLine::splitArcWith(Arc* arc, Arc* newArc)
{
	Arc* duplicate = createArc(arc->_site);
	duplicate->_leftEdge = newArc->_leftEdge;
	
	insertAfter(duplicate, arc);
	insertAfter(newArc, arc);
}

Arc* BeachLine::arcAbove(const Point& point) const
{
	real baselineY = point.y();
	
	for (Arc* arc=_firstElement; arc; arc=arc->next()) {
		if (!arc->next()) {
			if (arc->site()->position().y()==point.y()) return 0;
			return arc;
		}
		
		bool left = arc->site()->position().y()>arc->next()->site()->position().y();
		
		ParabolaIntersectionSolutionSet solutionSet = arc->parabola(baselineY).intersection(arc->next()->parabola(baselineY));
		if (solutionSet.isEmpty() || solutionSet.isInfinite()) {
			continue;
		}

		Point intersection = left ? solutionSet.leftPoint() : solutionSet.rightPoint();

		if (point.x()<=intersection.x()) {
			return arc;
		}
	}
	
	return 0;
}

Arc* BeachLine::lastElement() const
{
	return _lastElement;
}

void BeachLine::replaceArc(Arc* arc, VoronoiEdge* edge)
{
	Arc* prev = arc->prev();
	Arc* next = arc->next();
	
	if (!prev) {
		_firstElement = next;
	}
	
	if (next) {
		next->_leftEdge = edge;
	} else {
		_lastElement = prev;
	}
	
	unlinkArc(arc);
	delete arc;
}

void BeachLine::linkArcs(Arc* arc1, Arc* arc2)
{
	if (arc1) {
		arc1->_next = arc2;
	}
	if (arc2) {
		arc2->_prev = arc1;
	}
}

void BeachLine::unlinkArc(Arc* arc)
{
	Arc* _prev = arc->_prev;
	Arc* _next = arc->_next;
	
	if (_prev) {
		_prev->_next = _next;
	}
	if (_next) {
		_next->_prev = _prev;
	}
}
