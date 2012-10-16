#pragma once

#include <geometry/Point.h>

namespace voronoi {

class VoronoiSite
{
public:
	VoronoiSite();
	VoronoiSite(const geometry::Point& position);
	VoronoiSite(geometry::real x, geometry::real y);

	geometry::Point position() const;
protected:
	geometry::Point _position;
};

} //end namespace voronoi

