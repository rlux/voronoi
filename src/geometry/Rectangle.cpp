#include <geometry/Rectangle.h>
#include <algorithm>

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
