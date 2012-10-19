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

#pragma once

#include <VoronoiEdge.h>
#include <fortune/Arc.h>

namespace voronoi {
namespace fortune {

class BeachLine
{
public:
	BeachLine();

	Arc* createArc(VoronoiSite* site);

	bool isEmpty() const;
	void insert(Arc* arc);
	void insertAfter(Arc* newArc, Arc* after);
	void splitArcWith(Arc* arc, Arc* newArc);

	Arc* arcFor(const geometry::Point& p) const;
	void replaceArc(Arc* arc, VoronoiEdge* edge);
	Arc* lastElement() const;
private:
	Arc* _firstElement;
	Arc* _lastElement;

	void linkArcs(Arc* arc1, Arc* arc2);
	void unlinkArc(Arc* arc);
};

} //end namespace fortune
} //end namespace voronoi

