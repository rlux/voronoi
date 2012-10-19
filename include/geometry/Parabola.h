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

#include <geometry/Point.h>

namespace geometry {
	
class ParabolaIntersectionSolutionSet;

class Parabola
{
public:
	Parabola();
	Parabola(const Point& focus, real baselineY);

	const Point& focus() const;
	real baselineY() const;

	real operator()(real x) const;
	Point at(real x) const;

	const Point& vertex() const;
	real stretchFactor() const;

	// parabola formula: (x-h)^2 = 4a(y-k) with vertex=(h,k) and a=dist(line, vertex)/2
	real a() const;
	real h() const;
	real k() const;

	ParabolaIntersectionSolutionSet intersection(const Parabola& parabola) const;
protected:
	Point _focus;
	real _baselineY;

	real _stretchFactor;
	Point _vertex;
};

class ParabolaIntersectionSolutionSet
{
public:
	enum Type {
		NO_SOLUTION,
		ONE_SOLUTION,
		TWO_SOLUTIONS,
		INFINITE_SOLUTIONS
	};
	
	ParabolaIntersectionSolutionSet();
	ParabolaIntersectionSolutionSet(const Point& point);
	ParabolaIntersectionSolutionSet(const Point& point1, const Point& point2);
	
	static ParabolaIntersectionSolutionSet noSolution();
	static ParabolaIntersectionSolutionSet infiniteSolutions();
	
	bool isEmpty() const;
	bool isOne() const;
	bool isTwo() const;
	bool isInfinite() const;
	
	const Type& type() const;
	const Point& point() const;
	const Point& leftPoint() const;
	const Point& rightPoint() const;
private:
	Type _type;
	Point _leftPoint;
	Point _rightPoint;
};


} //end namespace geometry
