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

#include <voronoi_api.h>

#include <geometry/real.h>

namespace geometry {

class Point;

class Vector
{
public:
	Vector();
	Vector(real x, real y);

	real x() const;
	real y() const;
	void setX(real x);
	void setY(real y);
	
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;

	Vector operator-() const;
	Vector& operator+=(const Vector& v);
	Vector& operator-=(const Vector& v);
	Vector& operator*=(real factor);
	Vector& operator/=(real factor);
	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector operator*(real factor) const;
	Vector operator/(real factor) const;
	
	Point toPoint() const;

	real dotProduct(const Vector& v) const;
	real length() const;
	real squaredLength() const;
	
	bool isParallelTo(const Vector& v) const;
	
	Vector perpendicular() const;
private:
	real _x;
	real _y;
};

VORONOI_API Vector operator*(real factor, const Vector& v);

} //end namespace geometry
