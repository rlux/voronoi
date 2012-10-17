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

#include <geometry/Triangle.h>
#include <geometry/Line.h>

using namespace geometry;

Triangle::Triangle()
{
}

Triangle::Triangle(const Point& a, const Point& b, const Point& c) : a(a), b(b), c(c)
{
}

Circle Triangle::circumcircle() const
{
	Point ab = b-a;
	Point bc = c-b;
	
	if (ab.x()*bc.y()-ab.y()*bc.x()==0) return Circle(); // all points on a line
	
	LinearSolutionSet solutionSet = Line::forNormal((a+b)/2, ab).intersection(Line::forNormal((b+c)/2,bc));
	if (!solutionSet.isOne()) {
		return Circle();
	}
	
	Point center = solutionSet.point();
	real r = (center-a).length();
	
	return Circle(center, r);
}

bool Triangle::contains(const Point& p) const
{
	return Line::segment(b, c).sameSide(p, a) && Line::segment(a, c).sameSide(p, b) && Line::segment(a, b).sameSide(p, c);
}

bool Triangle::isClockwise() const
{
	Point ab(b-a);
	Point bc(c-b);
	return ab.x()*bc.y()-ab.y()*bc.x()<0;
}
