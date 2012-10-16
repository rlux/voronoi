#include <fortune/BeachLine.h>

using namespace voronoi;
using namespace voronoi::fortune;
using namespace geometry;

BeachLine::BeachLine() : firstElement(nullptr)
{
}

Arc* BeachLine::arcFor(const Point& p) const
{
	for (Arc* arc=firstElement; arc; arc=arc->next) {
		if (!arc->next) {
			if (arc->site->position().y()==p.y()) return nullptr;
			return arc;
		}
		
		bool left = arc->site->position().y()>arc->next->site->position().y();

		Point intersection = Arc::intersection(arc->site->position(), arc->next->site->position(), p.y(), left);
		if (!intersection.isValid()) continue;

		if (p.x()<=intersection.x()) {
			return arc;
		}
	}
	
	return nullptr;
}

Arc* BeachLine::lastElement() const
{
	Arc* last = firstElement;
	for (last; last->next; last = last->next);
	return last;
}

void BeachLine::replaceArc(Arc* arc, VoronoiEdge* edge)
{
	Arc* prev = arc->prev;
	Arc* next = arc->next;
	
	if (!prev) {
		firstElement = nullptr;
	}
	
	if (next) {
		next->leftEdge = edge;
	}
	
	Arc::remove(arc);
}
