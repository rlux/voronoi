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

#include <geometry/Circle.h>
#include <geometry/Line.h>

using namespace geometry;

Circle::Circle() : _center(Point()), _radius(0)
{
}

Circle::Circle(const Point& center, real radius) : _center(center), _radius(radius)
{
}

Circle::Circle(const Point& a, const Point& b, const Point& c)
{
	Vector ab = b-a;
	Vector bc = c-b;
	
	if (ab.x()*bc.y()-ab.y()*bc.x()==0) { // all points on a line
		return;
	}
	
	LineIntersectionSolutionSet solutionSet = Line::forNormal(a.midPoint(b), ab).intersection(Line::forNormal(b.midPoint(c),bc));
	if (!solutionSet.isOne()) {
		return;
	}
	
	_center = solutionSet.point();
	_radius = (_center-a).length();
}

const Point& Circle::center() const
{
	return _center;
}

real Circle::radius() const
{
	return _radius;
}

bool Circle::contains(const Point& p) const
{
	return (_center-p).squaredLength()<=_radius*_radius;
}

Point Circle::top() const
{
	return Point(_center.x(), _center.y() - _radius);
}

Point Circle::bottom() const
{
	return Point(_center.x(), _center.y() + _radius);
}

Point Circle::left() const
{
	return Point(_center.x() - _radius, _center.y());
}

Point Circle::right() const
{
	return Point(_center.x() + _radius, _center.y());
}
