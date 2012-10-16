#include <VoronoiEdge.h>

#include <unordered_map>
#include <iostream>

using namespace voronoi;
using namespace geometry;


VoronoiEdge::VoronoiEdge(VoronoiSite* left, VoronoiSite* right) : left(left), right(right)
{
	line = Line::forNormal((left->position()+right->position())/2,left->position()-right->position());
}

void VoronoiEdge::addPoint(const Point& point)
{
	line.addPoint(point);
}

void VoronoiEdge::adjustOrientation(const Point& awayPoint)
{
	if (Line::segment(left->position(), right->position()).sameSide(line.startPoint()+line.direction(), awayPoint)) {
		line.invertDirection();
	}
}

Line VoronoiEdge::getRenderLine(const Rectangle& boundingBox)
{
	Point a;
	Point b;

	switch (line.type()) {
		case Line::LINE:
			a = line.intersection(getIntersectedBorderLine(-line.direction(), boundingBox));
			b = line.intersection(getIntersectedBorderLine(line.direction(), boundingBox));
		break;
		case Line::RAY:
			a = line.startPoint();
			b = line.intersection(getIntersectedBorderLine(line.direction(), boundingBox));
		break;
		case Line::SEGMENT:
			a = line.startPoint();
			b = line.endPoint();
		break;
	}
	
	return Line::segment(a, b);
}

Line VoronoiEdge::getIntersectedBorderLine(const Point& direction, const Rectangle& boundingBox)
{
	if (direction.x()<0) { //left
		return Line::forDirection(Point(boundingBox.left(),0), Point(0,1));
	} else if (direction.y()<0) { //top
		return Line::forDirection(Point(0,boundingBox.top()), Point(1,0));
	} else if (direction.x()==0) { //bottom
		return Line::forDirection(Point(0,boundingBox.bottom()), Point(1,0));
	} else { //right
		return Line::forDirection(Point(boundingBox.right(),0), Point(0,1));
	}
}
