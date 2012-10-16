#pragma once

#include <VoronoiEdge.h>
#include <fortune/Arc.h>

namespace voronoi {
namespace fortune {

class BeachLine
{
public:
	BeachLine();

	Arc* arcFor(const geometry::Point& p) const;
	void replaceArc(Arc* arc, VoronoiEdge* edge);
	Arc* lastElement() const;

	Arc* firstElement;
};

} //end namespace fortune
} //end namespace voronoi

