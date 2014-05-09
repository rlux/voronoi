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

#include <voronoi/voronoi_api.h>

#include <voronoi/VoronoiSite.h>
#include <voronoi/VoronoiEdge.h>
#include <voronoi/geometry/Parabola.h>

namespace voronoi {
namespace fortune {

class CircleEvent;
class BeachLine;

class VORONOI_API Arc
{
public:
	friend class BeachLine;

	VoronoiSite* site() const;

	Arc* prev() const;
	Arc* next() const;

	VoronoiEdge* leftEdge() const;
	VoronoiEdge* rightEdge() const;

	geometry::Parabola parabola(geometry::real baselineY) const;

	void setLeftEdge(VoronoiEdge* leftEdge); //TODO: avoid public call

	void invalidateCircleEvent();
	void resetCircleEvent(CircleEvent* event);

	bool hasTwoDifferentNeighborSites() const;
protected:
	VoronoiSite* _site;
	BeachLine* beachLine;
	CircleEvent* _event;
	VoronoiEdge* _leftEdge;
	Arc* _prev;
	Arc* _next;

	Arc(BeachLine* beachLine, VoronoiSite* site);
};

} //end namespace fortune
} //end namespace voronoi

