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

#include <geometry/Vector.h>
#include <geometry/Point.h>
#include <cmath>

using namespace geometry;

Vector geometry::operator*(real factor, const Vector& v) {
	return v * factor;
}

Vector::Vector() : _x(0), _y(0)
{
}

Vector::Vector(real x, real y) : _x(x), _y(y)
{
}

Vector Vector::operator-() const {
	return Vector(-_x, -_y);
}

Vector& Vector::operator+=(const Vector& v) {
	_x += v._x;
	_y += v._y;
	
	return *this;
}

Vector& Vector::operator-=(const Vector& v) {
	_x -= v._x;
	_y -= v._y;
	
	return *this;
}

Vector& Vector::operator*=(real factor) {
	_x *= factor;
	_y *= factor;
	
	return *this;
}

Vector& Vector::operator/=(real factor) {
	_x /= factor;
	_y /= factor;
	
	return *this;
}

Vector Vector::operator+(const Vector& v) const {
	return Vector(_x + v._x, _y + v._y);
}

Vector Vector::operator-(const Vector& v) const {
	return Vector(_x - v._x, _y - v._y);
}

Vector Vector::operator*(real factor) const {
	return Vector(_x * factor, _y * factor);
}

Vector Vector::operator/(real factor) const {
	return Vector(_x / factor, _y / factor);
}

bool Vector::operator==(const Vector& v) const
{
	return _x == v._x && _y == v._y;
}

bool Vector::operator!=(const Vector& v) const
{
	return _x != v._x || _y != v._y;
}

real Vector::dotProduct(const Vector& v) const {
	return _x * v._x + _y * v._y;
}

real Vector::length() const {
	return std::sqrt(squaredLength());
}

real Vector::squaredLength() const {
	return _x * _x + _y * _y;
}

Vector Vector::perpendicular() const
{
	return Vector(-_y, _x);
}

real Vector::x() const
{
	return _x;
}

real Vector::y() const
{
	return _y;
}

Point Vector::toPoint() const
{
	return Point(_x, _y);
}
