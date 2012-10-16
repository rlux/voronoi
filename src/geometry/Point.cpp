#include <geometry/Point.h>
#include <functional>
#include <cmath>

using namespace geometry;

Point geometry::operator*(real factor, const Point& p) {
	return p * factor;
}

Point::Point() : _x(0), _y(0), valid(false)
{
}

Point::Point(real x, real y) : _x(x), _y(y), valid(true)
{
}

bool Point::operator==(const Point& p) const
{
	return _x == p._x && _y == p._y;
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

bool Point::isValid() const {
	return valid;
}

size_t PointHasher::operator()(const Point& p) const
{
	std::hash<real> hashFunction;
	
	return hashFunction(p.x()) ^ hashFunction(p.y());
}