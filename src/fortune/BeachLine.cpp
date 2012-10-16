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

using namespace voronoi;
using namespace voronoi::fortune;
using namespace geometry;

BeachLine::BeachLine() : firstElement(0)
{
}

bool BeachLine::isEmpty() const
{
	return firstElement==0;
}

void BeachLine::addLast(Arc* arc)
{
	if (!firstElement) {
		firstElement = arc;
	} else {
		lastElement()->insert(arc);
	}
}

Arc* BeachLine::arcFor(const Point& p) const
{
	for (Arc* arc=firstElement; arc; arc=arc->next) {
		if (!arc->next) {
			if (arc->site->position().y()==p.y()) return 0;
			return arc;
		}
		
		bool left = arc->site->position().y()>arc->next->site->position().y();

		Point intersection = Arc::intersection(arc->site->position(), arc->next->site->position(), p.y(), left);
		if (!intersection.isValid()) continue;

		if (p.x()<=intersection.x()) {
			return arc;
		}
	}
	
	return 0;
}

Arc* BeachLine::lastElement() const
{
	Arc* last = firstElement;
	for (last; last->next; last = last->next);
	return last;
}

void BeachLine::replaceArc(Arc* arc, VoronoiEdge* edge)
{
	Arc* prev = arc->prev;
	Arc* next = arc->next;
	
	if (!prev) {
		firstElement = 0;
	}
	
	if (next) {
		next->leftEdge = edge;
	}
	
	Arc::remove(arc);
}
