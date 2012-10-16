#pragma once

#include <stddef.h>

namespace geometry {

typedef double real;

class Point
{
public:
	Point();
	Point(real x, real y);

	real x() const;
	real y() const;
	void setX(real x);
	void setY(real y);
	bool isValid() const;
	
	bool operator==(const Point& p) const;
	Point operator-() const;
	Point& operator+=(const Point& p);
	Point& operator-=(const Point& p);
	Point& operator*=(real factor);
	Point& operator/=(real factor);
	Point operator+(const Point& p) const;
	Point operator-(const Point& p) const;
	Point operator*(real factor) const;
	Point operator/(real factor) const;

	/* vector operations */
	real dotProduct(const Point& p) const;
	real length() const;
	real squaredLength() const;
	
	Point perpendicular() const;
private:
	real _x;
	real _y;
	bool valid;
};

Point operator*(real factor, const Point& p);

class PointHasher
{
public:
	size_t operator()(const geometry::Point& p) const;
};

} //end namespace geometry
