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

#include <VoronoiDiagram.h>

#include <fortune/Fortune.h>
#include <algorithm>

using namespace voronoi;
using namespace geometry;

VoronoiDiagram::VoronoiDiagram()
{
}

VoronoiDiagram::~VoronoiDiagram()
{
	for (std::vector<VoronoiEdge*>::iterator it = _edges.begin(); it != _edges.end(); ++it) {
		delete *it;
	}
	
	for (std::map<VoronoiSite*, VoronoiCell*>::iterator it = _cells.begin(); it != _cells.end(); ++it) {
		delete it->second;
	}
}

VoronoiDiagram* VoronoiDiagram::create(const std::vector<VoronoiSite*>& sites)
{
	VoronoiDiagram* diagram = new VoronoiDiagram();
	diagram->initialize(sites);
	diagram->calculate();
	return diagram;
}

const std::vector<VoronoiSite*>& VoronoiDiagram::sites() const
{
	return _sites;
}

std::vector<VoronoiSite*>& VoronoiDiagram::sites()
{
	return _sites;
}

const std::vector<VoronoiEdge*>& VoronoiDiagram::edges() const
{
	return _edges;
}

std::vector<VoronoiEdge*>& VoronoiDiagram::edges()
{
	return _edges;
}

const std::map<VoronoiSite*, VoronoiCell*>& VoronoiDiagram::cells() const
{
	return _cells;
}

std::map<VoronoiSite*, VoronoiCell*>& VoronoiDiagram::cells()
{
	return _cells;
}

void VoronoiDiagram::initialize(const std::vector<VoronoiSite*>& sites)
{
	_sites = sites;
	for (std::vector<VoronoiSite*>::iterator it = _sites.begin(); it != _sites.end(); ++it) {
		_cells[*it] = new VoronoiCell(*it);
	}
}

void VoronoiDiagram::calculate()
{
	fortune::Fortune fortune;
	fortune(*this);
}

VoronoiEdge* VoronoiDiagram::createEdge(VoronoiSite* left, VoronoiSite* right)
{
	VoronoiEdge* edge = new VoronoiEdge(left, right);
	
	_edges.push_back(edge);
	_cells[left]->edges.push_back(edge);
	_cells[right]->edges.push_back(edge);
	
	return edge;
}

bool compareSites(VoronoiSite* site1, VoronoiSite* site2)
{
	return site1->position().x() < site2->position().x() &&  site1->position().y() < site2->position().y();
}

bool equalSites(VoronoiSite* site1, VoronoiSite* site2)
{
	return site1->position() == site2->position();
}

void VoronoiDiagram::removeDuplicates(std::vector<VoronoiSite*>& sites)
{
	std::sort(sites.begin(), sites.end(), compareSites);
	std::vector<VoronoiSite*>::iterator newEnd = std::unique(sites.begin(), sites.end(), equalSites);
	sites.resize(newEnd - sites.begin());
}
