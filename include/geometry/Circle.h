#pragma once

#include <geometry/Point.h>

namespace geometry {

class Circle
{
public:
	Circle();
	Circle(const Point& center, real radius);

	Point center() const;
	real radius() const;

	bool contains(const Point& p) const;
	bool isValid() const;
protected:
	Point _center;
	real _radius;
};

} //end namespace geometry
