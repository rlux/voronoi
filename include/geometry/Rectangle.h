#pragma once

#include <geometry/Point.h>

namespace geometry {

class Rectangle
{
public:
	Rectangle(const Point& a, const Point& b);
	Rectangle(real top, real left, real width, real height);
	
	real left() const;
	real right() const;
	real top() const;
	real bottom() const;
protected:
	real _top;
	real _left;
	real _height;
	real _width;
};

} //end namespace geometry
