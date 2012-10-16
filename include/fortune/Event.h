#pragma once

#include <VoronoiSite.h>
#include <fortune/Arc.h>
#include <geometry/Circle.h>

namespace voronoi {
namespace fortune {

class SiteEvent;
class CircleEvent;

class Event
{
public:
	virtual bool isSiteEvent() const;
	virtual bool isCircleEvent() const;
	SiteEvent* asSiteEvent() const;
	CircleEvent* asCircleEvent() const;
	virtual geometry::Point position() const = 0;
	
	bool operator<(const Event& event) const;
};

class SiteEvent : public Event
{
public:
	SiteEvent(VoronoiSite* site);

	virtual bool isSiteEvent() const;
	virtual geometry::Point position() const;

	VoronoiSite* site;
};
	
class CircleEvent : public Event
{
public:
	CircleEvent(Arc* arc, geometry::Circle circle);

	virtual geometry::Point position() const;
	virtual bool isCircleEvent() const;

	Arc* arc;
	geometry::Circle circle;
	bool valid;
};

class EventComparator
{
public:
	bool operator()(Event* event1, Event* event2);
};

} //end namespace fortune
} //end namespace voronoi

