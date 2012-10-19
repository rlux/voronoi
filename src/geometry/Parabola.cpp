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

#include <geometry/Parabola.h>
#include <algorithm>
#include <cmath>

using namespace geometry;

Parabola::Parabola()
{
}

Parabola::Parabola(const Point& focus, real baselineY) : _focus(focus), _baselineY(baselineY)
{
	_stretchFactor = (_focus.y()-_baselineY)/2;
	_vertex = Point(_focus.x(), _focus.y()-_stretchFactor);
}

const Point& Parabola::focus() const
{
	return _focus;
}

real Parabola::baselineY() const
{
	return _baselineY;
}

real Parabola::stretchFactor() const
{
	return _stretchFactor;
}

const Point& Parabola::vertex() const
{
	return _vertex;
}

real Parabola::a() const
{
	return _stretchFactor;
}

real Parabola::h() const
{
	return _vertex.x();
}

real Parabola::k() const
{
	return _vertex.y();
}

real Parabola::operator()(real x) const
{
	// parabola formula: (x-h)^2 = 4a(y-k) with vertex=(h,k) and a=dist(line, vertex)/2
	return (x-h())*(x-h())/(4*a())+k();
}

Point Parabola::at(real x) const
{
	return Point(x, (*this)(x));
}

ParabolaIntersectionSolutionSet Parabola::intersection(const Parabola& parabola) const
{
	real h1 = h();
	real k1 = k();
	real a1 = a();
	
	real h2 = parabola.h();
	real k2 = parabola.k();
	real a2 = parabola.a();
		
	real x;

	if (a1==0 && a2==0) { // no intersection
		return ParabolaIntersectionSolutionSet::noSolution();		
	}
	
	if (a1==a2) { // parabolas have same stretch factor
		x = (h1+h2)/2;
	} else if (a1==0) { // first parabola lies on baseline -> degenerates to point
		x = h1;
		return ParabolaIntersectionSolutionSet(parabola.at(x));
	} else if (a2==0) { // second parabola lies on baseline -> degenerates to point
		x = h2;
	} else { // two intersection points
		real p = 2*(h2*a1-h1*a2)/(a2-a1);
		real q = (4*a1*a2*(k1-k2)+h1*h1*a2-h2*h2*a1)/(a2-a1);
		real D = p*p/4-q;
		
		real sqrtD = sqrt(D);
		
		x = -p/2-sqrtD;
		real x2 = -p/2+sqrtD;

		return ParabolaIntersectionSolutionSet(at(x), at(x2));
	}
	
	return ParabolaIntersectionSolutionSet(at(x));
}

ParabolaIntersectionSolutionSet::ParabolaIntersectionSolutionSet() : _type(NO_SOLUTION)
{
}

ParabolaIntersectionSolutionSet::ParabolaIntersectionSolutionSet(const Point& point) : _type(ONE_SOLUTION), _leftPoint(point), _rightPoint(point)
{
}

ParabolaIntersectionSolutionSet::ParabolaIntersectionSolutionSet(const Point& point1, const Point& point2) : _type(TWO_SOLUTIONS), _leftPoint(point1), _rightPoint(point2)
{
	if (_leftPoint.x()>_rightPoint.x()) {
		std::swap(_leftPoint, _rightPoint);
	}
}

ParabolaIntersectionSolutionSet ParabolaIntersectionSolutionSet::noSolution()
{
	return ParabolaIntersectionSolutionSet();
}

ParabolaIntersectionSolutionSet ParabolaIntersectionSolutionSet::infiniteSolutions()
{
	ParabolaIntersectionSolutionSet solutionSet;
	solutionSet._type = INFINITE_SOLUTIONS;
	return solutionSet;
}

bool ParabolaIntersectionSolutionSet::isEmpty() const
{
	return _type==NO_SOLUTION;
}

bool ParabolaIntersectionSolutionSet::isOne() const
{
	return _type==ONE_SOLUTION;
}

bool ParabolaIntersectionSolutionSet::isTwo() const
{
	return _type==TWO_SOLUTIONS;
}

bool ParabolaIntersectionSolutionSet::isInfinite() const
{
	return _type==INFINITE_SOLUTIONS;
}

const ParabolaIntersectionSolutionSet::Type& ParabolaIntersectionSolutionSet::type() const
{
	return _type;
}

const Point& ParabolaIntersectionSolutionSet::point() const
{
	return _leftPoint;
}

const Point& ParabolaIntersectionSolutionSet::leftPoint() const
{
	return _leftPoint;
}

const Point& ParabolaIntersectionSolutionSet::rightPoint() const
{
	return _rightPoint;
}

