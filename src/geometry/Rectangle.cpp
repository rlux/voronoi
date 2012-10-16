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

#include <geometry/Rectangle.h>
#include <algorithm>
#include <cmath>

using namespace geometry;

Rectangle::Rectangle(const Point& a, const Point& b)
{
	_left = std::min(a.x(), b.x());
	_width = std::abs(a.x() - b.x());
	_top = std::min(a.y(), b.y());
	_height = std::abs(a.y() - b.y());
}

Rectangle::Rectangle(real top, real left, real width, real height) : _top(top), _left(left), _width(width), _height(height)
{
}

real Rectangle::left() const
{
	return _left;
}

real Rectangle::right() const
{
	return _left + _width;
}

real Rectangle::top() const
{
	return _top;
}

real Rectangle::bottom() const
{
	return _top + _height;
}
