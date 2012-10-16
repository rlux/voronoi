#pragma once

#include <geometry/Point.h>
#include <geometry/Line.h>
#include <geometry/Rectangle.h>

#include <VoronoiSite.h>

namespace voronoi {

class VoronoiEdge
{
public:
	VoronoiEdge(VoronoiSite* left, VoronoiSite* right);

	void addPoint(const geometry::Point& point);
	void adjustOrientation(const geometry::Point& awayPoint);

	geometry::Line getRenderLine(const geometry::Rectangle& boundingBox);
protected:
	VoronoiSite* left;
	VoronoiSite* right;

	geometry::Line line;
private:
	geometry::Line getIntersectedBorderLine(const geometry::Point& direction, const geometry::Rectangle& boundingBox);
};

} //end namespace voronoi

