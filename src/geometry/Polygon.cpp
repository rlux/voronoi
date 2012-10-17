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

#include <geometry/Polygon.h>

using namespace geometry;

Polygon::Polygon()
{
}

Polygon::Polygon(std::vector<Point> points) : _points(points)
{
}

const std::vector<Point>& Polygon::points() const
{
	return _points;
}

const std::vector<Line>& Polygon::edges() const
{
	return _edges;
}

bool Polygon::contains(const Point& p) const
{
	if (_edges.size() < 3) {
		return false;
	}
	
	for (unsigned i=0; i < _edges.size(); ++i) {
		Line& line = _edges[i]; // edge from points[i] to points[i+1]
		
		if (!line.sameSide(p, _points[(i+2)%_points.size())) {
			return false;
		}
	}
	
	return true;
}

Polygon& Polygon::operator<<(const Point& point)
{
	_points.push_back(point);
	
	if (_points.size() > 1) {
		if (_edges.size() > 0) {
			_edges.back().setEndPoint(point);
		}
		
		_edges.push_back(Line::segment(point, _points.front()));
	}
	
	return *this;
}
