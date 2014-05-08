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

#include <voronoi_api.h>

#include <geometry/Point.h>
#include <geometry/Line.h>
#include <geometry/Rectangle.h>
#include <vector>
#include <set>

namespace geometry {

class PolygonIntersectionSolutionSet;

class VORONOI_API ConvexPolygon
{
public:
	ConvexPolygon();
	ConvexPolygon(const std::vector<Point>& points);

	const std::vector<Point>& points() const;
	const std::vector<Line>& edges() const;
	bool contains(const Point& p) const;
	bool violatesConvexity(const Point& point) const;
	PolygonIntersectionSolutionSet intersection(const Line& line) const;
	const Rectangle& boundingBox() const;
	
	ConvexPolygon& operator<<(const Point& point);
protected:
	std::vector<Point> _points;
	std::vector<Line> _edges;
	Rectangle _boundingBox;
};

class VORONOI_API PolygonIntersectionSolutionSet
{
public:
	std::vector<Point> points() const;
	unsigned size() const;
	void addPoint(const Point& point);
protected:
	std::set<Point> _points;
};

} //end namespace geometry
