/**
  * (C) LGPL-3
  *
  * Voronoi++ <https://github.com/rlux/voronoi>
  *
  * Copyright: 2012 Lux, Scheibel
  * Authors:
  *     Roland Lux <rollux2000@googlemail.com>
  *     Willy Scheibel <willyscheibel@gmx.de>
  * 
  * This file is part of Voronoi++.
  *
  * Voronoi++ is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Lesser General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  * 
  * Voronoi++ is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU Lesser General Public License for more details.
  * 
  * You should have received a copy of the GNU Lesser General Public License
  * along with Voronoi++.  If not, see <http://www.gnu.org/licenses/>.
  **/

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
	virtual ~Event();
	
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

	VoronoiSite* site() const;
private:
	VoronoiSite* _site;
};
	
class CircleEvent : public Event
{
public:
	CircleEvent(Arc* arc, geometry::Circle circle);

	virtual bool isCircleEvent() const;
	virtual geometry::Point position() const;

	bool isValid() const;
	void invalidate();
	Arc* arc() const;
	const geometry::Circle& circle() const;
private:
	Arc* _arc;
	geometry::Circle _circle;
	bool valid;
};

class EventComparator
{
public:
	bool operator()(Event* event1, Event* event2);
};

} //end namespace fortune
} //end namespace voronoi

