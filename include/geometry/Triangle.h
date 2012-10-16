#pragma once

#include <geometry/Point.h>
#include <geometry/Circle.h>

namespace geometry {

class Triangle
{
public:
	Triangle(const Point& a, const Point& b, const Point& c);

	Circle circumcircle() const;
	bool contains(const Point& p) const;
	bool isClockwise() const;
protected:
	Point a;
	Point b;
	Point c;
};

} //end namespace geometry
