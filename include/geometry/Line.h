#pragma once

#include <geometry/Point.h>

namespace geometry {

class Line
{
public:
	enum Type {
		NULL_LINE,
		LINE,
		RAY,
		SEGMENT
	};

	Line();
	
	static Line forDirection(const Point& supportVector, const Point& direction);
	static Line forNormal(const Point& supportVector, const Point& normal);
	
	static Line ray(const Point& supportVector, const Point& direction);
	static Line segment(const Point& point1, const Point& point2);
	
	Point startPoint() const;
	Point direction() const;
	Point endPoint() const;
	Type type() const;
	
	void invertDirection();
	bool addPoint(const Point& point);

	Point intersection(const Line& line) const;
	Point normal() const;
	Point toPoint(const Point& point) const; //TODO: rename (to let fall a perpendicular?)
	//
	bool sameSide(const Point& p1, const Point& p2) const;
protected:
	Point _startPoint;
	Point _direction;
	
	Type _type;
};


} //end namespace geometry
