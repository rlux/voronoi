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

#include <geometry/ConvexPolygon.h>
#include <stdexcept>

using namespace geometry;

ConvexPolygon::ConvexPolygon()
{
}

ConvexPolygon::ConvexPolygon(const std::vector<Point>& points)
{
	for (std::vector<Point>::const_iterator it = points.begin(); it != points.end(); ++it) {
		*this << *it;
	}
}

const std::vector<Point>& ConvexPolygon::points() const
{
	return _points;
}

const std::vector<Line>& ConvexPolygon::edges() const
{
	return _edges;
}

bool ConvexPolygon::contains(const Point& p) const
{
	if (_edges.size() < 3) {
		return false;
	}
	
	for (unsigned i=0; i < _edges.size(); ++i) {
		const Line& line = _edges[i]; // edge from points[i] to points[i+1]
		
		if (!line.sameSide(p, _points[(i+2)%_points.size()])) {
			return false;
		}
	}
	
	return true;
}

PolygonIntersectionSolutionSet ConvexPolygon::intersection(const Line& line) const
{
	bool containsStartPoint = (line.isSegment() || line.isRay()) && contains(line.startPoint());
	bool containsEndPoint = line.isSegment() && contains(line.endPoint());
	
	if (containsStartPoint && containsEndPoint) {
		return PolygonIntersectionSolutionSet();
	}
	
	PolygonIntersectionSolutionSet result;
	
	int maximumNumberOfIntersections = (containsStartPoint ? 0 : 1) + (containsEndPoint ? 0 : 1);
	
	for (std::vector<Line>::const_iterator it = _edges.begin(); it != _edges.end(); ++it) {
		const Line& edge = *it;
		
		LineIntersectionSolutionSet solutionSet = line.intersection(edge);
		
		if (solutionSet.isOne()) {
			result.addPoint(solutionSet.point());
		}
		
		if (result.size() >= maximumNumberOfIntersections) {
			break;
		}
	}
	
	return result;
}

const Rectangle& ConvexPolygon::boundingBox() const
{
	return _boundingBox;
}

ConvexPolygon& ConvexPolygon::operator<<(const Point& point)
{
	if (violatesConvexity(point)) {
		throw std::runtime_error("Point violates convexity of polygon");
	}
	
	_points.push_back(point);
	_boundingBox.resizeToInclude(point);
	
	if (_points.size() >= 1) {
		if (_edges.size() > 0) {
			_edges.back().setEndPoint(point);
		}
		
		_edges.push_back(Line::segment(point, _points.front()));
	}
	
	return *this;
}

bool ConvexPolygon::violatesConvexity(const Point& point) const
{
	if (_points.size() < 3) {
		return false;
	}
	
	return clockwise(_points[0], _points[1], _points[2]) != clockwise(_points[_points.size()-2], _points[_points.size()-1], point);
}

std::vector<Point> PolygonIntersectionSolutionSet::points() const
{
	return std::vector<Point>(_points.begin(), _points.end());
}

unsigned PolygonIntersectionSolutionSet::size() const
{
	return _points.size();
}

void PolygonIntersectionSolutionSet::addPoint(const Point& point)
{
	_points.insert(point);
}
