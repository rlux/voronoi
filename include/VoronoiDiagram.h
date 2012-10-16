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

#include <vector>
#include <map>

#include <VoronoiSite.h>
#include <VoronoiEdge.h>
#include <VoronoiCell.h>

namespace voronoi {

class VoronoiDiagram
{
public:
	VoronoiDiagram();
	~VoronoiDiagram();

	static VoronoiDiagram create(const std::vector<VoronoiSite*>& sites);
	static void removeDuplicates(std::vector<VoronoiSite*>& sites);

	const std::vector<VoronoiSite*>& sites() const;
	std::vector<VoronoiSite*>& sites();
	const std::vector<VoronoiEdge*>& edges() const;
	std::vector<VoronoiEdge*>& edges();
	const std::map<VoronoiSite*, VoronoiCell*>& cells() const;
	std::map<VoronoiSite*, VoronoiCell*>& cells();

	void initialize(const std::vector<VoronoiSite*>& sites);
	void calculate();
	VoronoiEdge* createEdge(VoronoiSite* left, VoronoiSite* right);
protected:
	std::vector<VoronoiSite*> _sites;
	std::vector<VoronoiEdge*> _edges;
	std::map<VoronoiSite*, VoronoiCell*> _cells;
};

} //end namespace voronoi

