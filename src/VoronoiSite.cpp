#include <VoronoiSite.h>


using namespace voronoi;
using namespace geometry;

VoronoiSite::VoronoiSite()
{
}

VoronoiSite::VoronoiSite(const Point& position) : _position(position)
{
}

VoronoiSite::VoronoiSite(real x, real y) : _position(x, y)
{
}

geometry::Point VoronoiSite::position() const
{
	return _position;
}
