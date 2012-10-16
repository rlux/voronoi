#include <geometry/Circle.h>

using namespace geometry;

Circle::Circle() : _center(Point()), _radius(0)
{
}

Circle::Circle(const Point& center, real radius) : _center(center), _radius(radius)
{
}

Point Circle::center() const
{
	return _center;
}

real Circle::radius() const
{
	return _radius;
}

bool Circle::contains(const Point& p) const
{
	return (_center-p).squaredLength()<=_radius*_radius;
}

bool Circle::isValid() const
{
	return _center.isValid() && _radius>=0;
}
