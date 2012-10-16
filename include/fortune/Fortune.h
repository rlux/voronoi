#pragma once

#include <vector>
#include <queue>

#include <VoronoiDiagram.h>
#include <fortune/Event.h>
#include <fortune/BeachLine.h>

namespace voronoi {
namespace fortune {

class Fortune
{
public:
	Fortune();

	void operator()(VoronoiDiagram& diagram);
private:
	VoronoiDiagram diagram;

	std::priority_queue<Event*, std::vector<Event*>, EventComparator> eventQueue;
	BeachLine beachLine;
	geometry::real sweepPos;

	void calculate();

	Event* nextEvent();
	void addEvent(Event* event);

	void handleSiteEvent(SiteEvent* event);
	void handleCircleEvent(CircleEvent* event);

	void checkCircleEvent(Arc* arc);
};

} //end namespace fortune
} //end namespace voronoi

