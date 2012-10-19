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

#include <VoronoiSite.h>
#include <VoronoiEdge.h>
#include <geometry/Triangle.h>

namespace voronoi {
namespace fortune {

class CircleEvent;
class BeachLine;

class Arc
{
public:
	friend class BeachLine;

	VoronoiSite* site() const;

	/*void insert(Arc* arc);
	void splitWith(Arc* arc);*/

	void invalidateEvent();

	VoronoiEdge* rightEdge();

	bool getTriangle(geometry::Triangle& triangle) const; //TODO: find better name

	//TODO: return solution set
	static geometry::Point intersection(const geometry::Point& focus1, const geometry::Point& focus2, geometry::real baseLineY, bool left, bool& intersects);

	VoronoiEdge* leftEdge;
	
	Arc* prev;
	Arc* next;

	CircleEvent* event;
protected:
	VoronoiSite* _site;
	BeachLine* beachLine;

	Arc(BeachLine* beachLine, VoronoiSite* site);

	static void connect(Arc* arc1, Arc* arc2);
	static void remove(Arc* arc);
};

} //end namespace fortune
} //end namespace voronoi

