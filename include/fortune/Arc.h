#pragma once

#include <VoronoiSite.h>
#include <VoronoiEdge.h>

namespace voronoi {
namespace fortune {

class CircleEvent;

class Arc
{
public:
	Arc(VoronoiSite* site, VoronoiEdge* leftEdge = nullptr);
	~Arc();

	void insert(Arc* arc);
	void splitWith(Arc* arc);

	void invalidateEvent();

	VoronoiEdge* rightEdge();

	static geometry::Point intersection(const geometry::Point& focus1, const geometry::Point& focus2, geometry::real baseLineY, bool left);
	static void connect(Arc* arc1, Arc* arc2);
	static void remove(Arc* arc);

	VoronoiSite* site;

	VoronoiEdge* leftEdge;

	Arc* prev;
	Arc* next;

	CircleEvent* event;
};

} //end namespace fortune
} //end namespace voronoi

