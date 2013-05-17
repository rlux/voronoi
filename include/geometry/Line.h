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
#include <geometry/Vector.h>

namespace geometry {
	
class LineIntersectionSolutionSet;

class Line
{
public:
	enum Type {
		NULL_LINE,
		LINE,
		RAY,
		SEGMENT
	};

	Line();
	
	static Line forDirection(const Point& supportVector, const Vector& direction);
	static Line forNormal(const Point& supportVector, const Vector& normal);
	
	static Line ray(const Point& supportVector, const Vector& direction);
	static Line segment(const Point& point1, const Point& point2);
	
	const Point& supportVector() const;
	const Point& startPoint() const;
	const Vector& direction() const;
	const Point& endPoint() const;
	Type type() const;
	
	bool isNull() const;
	bool isLine() const;
	bool isRay() const;
	bool isSegment() const;
	
	Line asLine() const;
	
	void setStartPoint(const Point& point);
	void setEndPoint(const Point& point);
	void setDirection(const Vector& direction);
	
	void invertDirection();
	bool addPoint(const Point& point);

	LineIntersectionSolutionSet intersection(const Line& line) const;
	Vector normal() const;
	Line perpendicular(const Point& point) const;
	
	bool isParallelTo(const Line& line) const;
	bool contains(const Point& p) const;
	bool overlaps(const Line& line) const;
	bool sameSide(const Point& p1, const Point& p2) const;
protected:
	Point _startPoint;
	Vector _direction;
	Point _endPoint;	
	Type _type;

	Line(Type type, const Point& start, const Point& end, const Vector& direction);

	bool lineContains(const Point& p) const;
	bool intersectionCoefficient(const Line& line, real& coefficient) const;
	LineIntersectionSolutionSet lineIntersection(const Line& line) const;
	bool containsCoefficient(real coefficient) const;
	real coefficientForPointOnLine(const Point& p) const;
};

class LineIntersectionSolutionSet
{
public:
	enum Type {
		NO_SOLUTION,
		ONE_SOLUTION,
		INFINITE_SOLUTIONS
	};
	
	LineIntersectionSolutionSet();
	LineIntersectionSolutionSet(const Point& point);
	
	static LineIntersectionSolutionSet noSolution();
	static LineIntersectionSolutionSet infiniteSolutions();
	
	bool isEmpty() const;
	bool isOne() const;
	bool isInfinite() const;
	
	Type type() const;
	const Point& point() const;
private:
	Type _type;
	Point _point;
};


} //end namespace geometry
