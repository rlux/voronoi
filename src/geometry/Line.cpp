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

#include <geometry/Line.h>

using namespace geometry;

Line::Line() : _type(NULL_LINE)
{
}

Line Line::segment(const Point& point1, const Point& point2) {
	Line line;
	line._startPoint = point1;
	line._direction = point2-point1;
	line._type = SEGMENT;
	return line;
}

Line Line::ray(const Point& supportVector, const Point& direction) {
	Line line;
	line._startPoint = supportVector;
	line._direction = direction;
	line._type = RAY;
	return line;
}

Line Line::forDirection(const Point& supportVector, const Point& direction)
{
	Line line;
	line._startPoint = supportVector;
	line._direction = direction;
	line._type = LINE;
	return line;
}

Line Line::forNormal(const Point& supportVector, const Point& normal)
{
	return Line::forDirection(supportVector, normal.perpendicular());
}

Point Line::startPoint() const
{
	return _startPoint;
}

Point Line::direction() const
{
	return _direction;
}

Point Line::endPoint() const
{
	if (_type==RAY) return Point();
	return _startPoint+_direction;
}

Line::Type Line::type() const
{
	return _type;
}

void Line::invertDirection()
{
	_direction *= -1;
}

bool Line::addPoint(const Point& point)
{
	switch (_type) {
		case LINE:
			_startPoint = point;
			_type = RAY;
			return true;
		case RAY:
			_direction = point - _startPoint;
			_type = SEGMENT;
			return true;
		default:
			return false;
	}
}

LinearSolutionSet Line::intersection(const Line& line) const
{
	Point u = _direction;
	Point v = line._direction;
	Point w = _startPoint-line._startPoint;
	real denominator = v.x()*u.y()-v.y()*u.x();
	if (denominator==0) {
		//check for infinite solutions: w parallel to u
		//extract vector class, parallelTo()
		return LinearSolutionSet::noSolution();
	}
	real s = (v.y()*w.x()-v.x()*w.y())/denominator;
	return LinearSolutionSet(_startPoint+s*_direction);
}

Point Line::normal() const
{
	return _direction.perpendicular();
}

Point Line::toPoint(const Point& point) const
{
	return point-intersection(Line::forDirection(point, normal())).point();
}

bool Line::sameSide(const Point& p1, const Point& p2) const
{
	return toPoint(p1).dotProduct(toPoint(p2))>=0;
}


LinearSolutionSet::LinearSolutionSet() : _type(NO_SOLUTION)
{
}

LinearSolutionSet::LinearSolutionSet(const Point& point) : _point(point), _type(ONE_SOLUTION)
{
}

LinearSolutionSet LinearSolutionSet::noSolution()
{
	return LinearSolutionSet();
}

LinearSolutionSet LinearSolutionSet::infiniteSolutions()
{
	LinearSolutionSet solutionSet;
	solutionSet._type = INFINITE_SOLUTIONS;
	return solutionSet;
}

bool LinearSolutionSet::isEmpty() const
{
	return _type==NO_SOLUTION;
}

bool LinearSolutionSet::isOne() const
{
	return _type==ONE_SOLUTION;
}

bool LinearSolutionSet::isInfinite() const
{
	return _type==INFINITE_SOLUTIONS;
}

const LinearSolutionSet::Type& LinearSolutionSet::type() const
{
	return _type;
}

const Point& LinearSolutionSet::point() const
{
	return _point;
}

