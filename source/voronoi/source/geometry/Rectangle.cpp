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

#include <algorithm>
#include <cmath>

#include <voronoi/geometry/Rectangle.h>

using namespace geometry;

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(const Point& a, const Point& b)
{
	_left = std::min(a.x(), b.x());
	_width = std::abs(a.x() - b.x());
	_top = std::min(a.y(), b.y());
	_height = std::abs(a.y() - b.y());
}

Rectangle::Rectangle(real left, real top, real width, real height) : _left(left), _top(top), _width(width), _height(height)
{
}

real Rectangle::x() const
{
	return _left;
}

real Rectangle::y() const
{
	return _top;
}

real Rectangle::width() const
{
	return _width;
}

real Rectangle::height() const
{
	return _height;
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

Point Rectangle::topLeft() const
{
	return Point(top(), left());
}

Point Rectangle::topRight() const
{
	return Point(top(), right());
}

Point Rectangle::bottomLeft() const
{
	return Point(bottom(), left());
}

Point Rectangle::bottomRight() const
{
	return Point(bottom(), right());
}

bool Rectangle::contains(const Point& p) const
{
	return left() <= p.x() && p.x() <= right() && top() <= p.y() && p.y() <= bottom();
}

void Rectangle::resizeToInclude(const Point& p)
{
	if (contains(p)) {
		return;
	}
	
	if (p.x() < left()) {
		_width += left() - p.x();
		_left = p.x();
	} else if (p.x() > right()) {
		_width += p.x() - right();
	}
	
	if (p.y() < top()) {
		_height += top() - p.y();
		_top = p.y();
	} else if (p.y() > bottom()) {
		_height += p.y() - bottom();
	}
}
