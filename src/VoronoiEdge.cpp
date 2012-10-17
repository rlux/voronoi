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

#include <VoronoiEdge.h>

using namespace voronoi;
using namespace geometry;

VoronoiEdge::VoronoiEdge(VoronoiSite* left, VoronoiSite* right) : left(left), right(right)
{
	line = Line::forNormal((left->position()+right->position())/2,left->position()-right->position());
}

void VoronoiEdge::addPoint(const Point& point)
{
	line.addPoint(point);
}

void VoronoiEdge::adjustOrientation(const Point& awayPoint)
{
	if (Line::segment(left->position(), right->position()).sameSide(line.startPoint()+line.direction(), awayPoint)) {
		line.invertDirection();
	}
}

Line VoronoiEdge::getRenderLine(const Rectangle& boundingBox)
{
	Point a;
	Point b;

	bool intersects = false;
	
	switch (line.type()) {
		case Line::LINE:
			a = line.intersection(getIntersectedBorderLine(-line.direction(), boundingBox), intersects);
			b = line.intersection(getIntersectedBorderLine(line.direction(), boundingBox), intersects);
		break;
		case Line::RAY:
			a = line.startPoint();
			b = line.intersection(getIntersectedBorderLine(line.direction(), boundingBox), intersects);
		break;
		case Line::SEGMENT:
			a = line.startPoint();
			b = line.endPoint();
		break;
	}
	
	return Line::segment(a, b);
}

Line VoronoiEdge::getIntersectedBorderLine(const Point& direction, const Rectangle& boundingBox)
{
	if (direction.x()<0) { //left
		return Line::forDirection(Point(boundingBox.left(),0), Point(0,1));
	} else if (direction.y()<0) { //top
		return Line::forDirection(Point(0,boundingBox.top()), Point(1,0));
	} else if (direction.x()==0) { //bottom
		return Line::forDirection(Point(0,boundingBox.bottom()), Point(1,0));
	} else { //right
		return Line::forDirection(Point(boundingBox.right(),0), Point(0,1));
	}
}
