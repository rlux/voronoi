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

#include <voronoi/geometry/Point.h>
#include <voronoi/geometry/Line.h>
#include <voronoi/geometry/Rectangle.h>
#include <voronoi/geometry/ConvexPolygon.h>

#include <voronoi/VoronoiSite.h>

namespace voronoi {
	
class VoronoiHalfEdge;

class VORONOI_API VoronoiEdge
{
public:
	VoronoiEdge(VoronoiSite* left, VoronoiSite* right);
	~VoronoiEdge();

	void addPoint(const geometry::Point& point);
	void adjustOrientation(const geometry::Point& awayPoint);

	VoronoiHalfEdge* halfEdgeFor(VoronoiSite* site);

	geometry::Line getRenderLine(const geometry::Rectangle& boundingBox) const;
	geometry::Line getRenderLine(const geometry::ConvexPolygon& boundingPolygon) const;
protected:
	VoronoiSite* left;
	VoronoiSite* right;

	geometry::Line line;

	VoronoiHalfEdge* halfEdge1;
	VoronoiHalfEdge* halfEdge2;
};

class VORONOI_API VoronoiHalfEdge
{
public:
	VoronoiHalfEdge(VoronoiSite* site);

	VoronoiSite* site() const;
	VoronoiHalfEdge* opposite() const;
	VoronoiHalfEdge* next() const;
	VoronoiHalfEdge* prev() const;
	const geometry::Point& startPoint() const;
	bool hasStartPoint() const;

	void setStartPoint(const geometry::Point& point);
	void setOpposite(VoronoiHalfEdge* opposite);
	void setNext(VoronoiHalfEdge* next);
	void setPrev(VoronoiHalfEdge* prev);

	VoronoiHalfEdge* begin();
protected:
	VoronoiHalfEdge* _opposite;
	VoronoiHalfEdge* _next;
	VoronoiHalfEdge* _prev;
	VoronoiSite* _site;
	geometry::Point _startPoint;
	bool _hasStart;
};

} //end namespace voronoi

