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

#include <geometry/Point.h>
#include <functional>
#include <cmath>

using namespace geometry;

Point geometry::operator*(real factor, const Point& p) {
	return p * factor;
}

Point::Point() : _x(0), _y(0)
{
}

Point::Point(real x, real y) : _x(x), _y(y)
{
}

Point Point::operator-() const {
	return Point(-_x, -_y);
}

Point& Point::operator+=(const Point& p) {
	_x += p._x;
	_y += p._y;
	
	return *this;
}

Point& Point::operator-=(const Point& p) {
	_x -= p._x;
	_y -= p._y;
	
	return *this;
}

Point& Point::operator*=(real factor) {
	_x *= factor;
	_y *= factor;
	
	return *this;
}

Point& Point::operator/=(real factor) {
	_x /= factor;
	_y /= factor;
	
	return *this;
}

Point Point::operator+(const Point& p) const {
	return Point(_x + p._x, _y + p._y);
}

Point Point::operator-(const Point& p) const {
	return Point(_x - p._x, _y - p._y);
}

Point Point::operator*(real factor) const {
	return Point(_x * factor, _y * factor);
}

Point Point::operator/(real factor) const {
	return Point(_x / factor, _y / factor);
}

bool Point::operator==(const Point& p) const
{
	return _x == p._x && _y == p._y;
}

bool Point::operator!=(const Point& p) const
{
	return _x != p._x || _y != p._y;
}

bool Point::operator<(const Point& p) const
{
	return _x < p._x || _y < p._y;
}

bool Point::operator<=(const Point& p) const
{
	return _x <= p._x || _y <= p._y;
}

bool Point::operator>(const Point& p) const
{
	return _x > p._x || _y > p._y;
}

bool Point::operator>=(const Point& p) const
{
	return _x >= p._x || _y >= p._y;
}

real Point::dotProduct(const Point& p) const {
	return _x * p._x + _y * p._y;
}

real Point::length() const {
	return std::sqrt(squaredLength());
}

real Point::squaredLength() const {
	return _x * _x + _y * _y;
}

Point Point::perpendicular() const
{
	return Point(-_y, _x);
}

real Point::x() const {
	return _x;
}

real Point::y() const {
	return _y;
}
