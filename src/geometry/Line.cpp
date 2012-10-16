#include <geometry/Line.h>

using namespace geometry;

Line::Line() : _type(NULL_LINE)
{
}

Line Line::segment(const Point& point1, const Point& point2) {
	Line line;
	line._startPoint = point1;
	line._direction = point2-point1;
	line._type = SEGMENT;
	return line;
}

Line Line::ray(const Point& supportVector, const Point& direction) {
	Line line;
	line._startPoint = supportVector;
	line._direction = direction;
	line._type = RAY;
	return line;
}

Line Line::forDirection(const Point& supportVector, const Point& direction)
{
	Line line;
	line._startPoint = supportVector;
	line._direction = direction;
	line._type = LINE;
	return line;
}

Line Line::forNormal(const Point& supportVector, const Point& normal)
{
	return Line::forDirection(supportVector, normal.perpendicular());
}

Point Line::startPoint() const
{
	return _startPoint;
}

Point Line::direction() const
{
	return _direction;
}

Point Line::endPoint() const
{
	if (_type==RAY) return Point();
	return _startPoint+_direction;
}

Line::Type Line::type() const
{
	return _type;
}

void Line::invertDirection()
{
	_direction *= -1;
}

bool Line::addPoint(const Point& point)
{
	switch (_type) {
		case LINE:
			_startPoint = point;
			_type = RAY;
			return true;
		case RAY:
			_direction = point - _startPoint;
			_type = SEGMENT;
			return true;
		default:
			return false;
	}
}

Point Line::intersection(const Line& line) const
{
	Point u = _direction;
	Point v = line._direction;
	Point w = _startPoint-line._startPoint;
	real denominator = v.x()*u.y()-v.y()*u.x();
	if (denominator==0) return Point();
	real s = (v.y()*w.x()-v.x()*w.y())/denominator;
	return _startPoint+s*_direction;
}

Point Line::normal() const
{
	return _direction.perpendicular();
}

Point Line::toPoint(const Point& point) const
{
	return point-intersection(Line::forDirection(point, normal()));
}

bool Line::sameSide(const Point& p1, const Point& p2) const
{
	return toPoint(p1).dotProduct(toPoint(p2))>=0;
}
