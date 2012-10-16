#pragma once

#include <VoronoiSite.h>
#include <VoronoiEdge.h>

#include <vector>

namespace voronoi {

class VoronoiCell
{
public:
	VoronoiCell(VoronoiSite* site);

	VoronoiSite* site;
	std::vector<VoronoiEdge*> edges;
};

} //end namespace voronoi
