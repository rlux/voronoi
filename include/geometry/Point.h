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

#include <stddef.h>

namespace geometry {

typedef double real;

class Point
{
public:
	Point();
	Point(real x, real y);

	real x() const;
	real y() const;
	void setX(real x);
	void setY(real y);
	bool isValid() const;
	
	bool operator==(const Point& p) const;
	Point operator-() const;
	Point& operator+=(const Point& p);
	Point& operator-=(const Point& p);
	Point& operator*=(real factor);
	Point& operator/=(real factor);
	Point operator+(const Point& p) const;
	Point operator-(const Point& p) const;
	Point operator*(real factor) const;
	Point operator/(real factor) const;

	/* vector operations */
	real dotProduct(const Point& p) const;
	real length() const;
	real squaredLength() const;
	
	Point perpendicular() const;
private:
	real _x;
	real _y;
	bool valid;
};

Point operator*(real factor, const Point& p);

class PointHasher
{
public:
	size_t operator()(const geometry::Point& p) const;
};

} //end namespace geometry
