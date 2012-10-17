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
	
class LinearSolutionSet;

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
	
	static Line forDirection(const Point& supportVector, const Point& direction);
	static Line forNormal(const Point& supportVector, const Point& normal);
	
	static Line ray(const Point& supportVector, const Point& direction);
	static Line segment(const Point& point1, const Point& point2);
	
	Point startPoint() const;
	Point direction() const;
	Point endPoint() const;
	Type type() const;
	
	void invertDirection();
	bool addPoint(const Point& point);

	LinearSolutionSet intersection(const Line& line) const;
	Point normal() const;
	Point toPoint(const Point& point) const; //TODO: rename (to let fall a perpendicular?)
	//
	bool sameSide(const Point& p1, const Point& p2) const;
protected:
	Point _startPoint;
	Point _direction;
	
	Type _type;
};

class LinearSolutionSet
{
public:
	enum Type {
		NO_SOLUTION,
		ONE_SOLUTION,
		INFINITE_SOLUTIONS
	};
	
	LinearSolutionSet();
	LinearSolutionSet(const Point& point);
	
	static LinearSolutionSet noSolution();
	static LinearSolutionSet infiniteSolutions();
	
	bool isEmpty() const;
	bool isOne() const;
	bool isInfinite() const;
	
	const Type& type() const;
	const Point& point() const;
private:
	Type _type;
	Point _point;
};


} //end namespace geometry
