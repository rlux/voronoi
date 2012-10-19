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
	line = Line::forNormal(left->position().midPoint(right->position()),left->position()-right->position());
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

Line VoronoiEdge::getRenderLine(const Rectangle& boundingBox) const
{
	ConvexPolygon boundingPolygon;
	
	boundingPolygon
		<< boundingBox.topLeft()
		<< boundingBox.topRight()
		<< boundingBox.bottomRight()
		<< boundingBox.bottomLeft();
	
	return getRenderLine(boundingPolygon);
}

Line VoronoiEdge::getRenderLine(const ConvexPolygon& boundingPolygon) const
{
	if (line.isSegment() && boundingPolygon.contains(line.startPoint()) && boundingPolygon.contains(line.endPoint())) {
		return line;
	}
	
	const PolygonIntersectionSolutionSet solutionSet = boundingPolygon.intersection(line);
	
	switch (solutionSet.size()) {
		case 0:
			return Line();
		case 1:
			if (boundingPolygon.contains(line.startPoint())) {
				return Line::segment(line.startPoint(), solutionSet.points().front());
			} else {
				return Line::segment(solutionSet.points().front(), line.endPoint());
			}
		default:
			const std::vector<Point> points = solutionSet.points();
			
			return Line::segment(points.front(), points.back());
	}
}
