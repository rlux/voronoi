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

#include <unordered_map>

#include <fortune/Fortune.h>

using namespace voronoi;
using namespace geometry;

VoronoiDiagram::VoronoiDiagram() : data(new Data())
{
}

VoronoiDiagram::Data::~Data()
{
	for (VoronoiEdge* edge: edges) {
		delete edge;
	}
	for (std::pair<VoronoiSite*, VoronoiCell*> pair: cells) {
		delete pair.second;
	}
}

VoronoiDiagram VoronoiDiagram::create(const std::vector<VoronoiSite>& sites)
{
	VoronoiDiagram diagram;
	diagram.initialize(sites);
	diagram.calculate();
	return diagram;
}

const std::vector<VoronoiSite>& VoronoiDiagram::sites() const
{
	return data->sites;
}

std::vector<VoronoiSite>& VoronoiDiagram::sites()
{
	return data->sites;
}

const std::vector<VoronoiEdge*>& VoronoiDiagram::edges() const
{
	return data->edges;
}

std::vector<VoronoiEdge*>& VoronoiDiagram::edges()
{
	return data->edges;
}

const std::map<VoronoiSite*, VoronoiCell*>& VoronoiDiagram::cells() const
{
	return data->cells;
}

std::map<VoronoiSite*, VoronoiCell*>& VoronoiDiagram::cells()
{
	return data->cells;
}

void VoronoiDiagram::clear()
{
	data.reset(new Data());
}

void VoronoiDiagram::initialize(const std::vector<VoronoiSite>& sites)
{
	this->sites() = sites;
	for (VoronoiSite& site: this->sites()) {
		cells()[&site] = new VoronoiCell(&site);
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
	
	edges().push_back(edge);
	cells()[left]->edges.push_back(edge);
	cells()[right]->edges.push_back(edge);
	
	return edge;
}

void VoronoiDiagram::removeDuplicates(std::vector<VoronoiSite>& sites)
{
	std::unordered_map<Point, VoronoiSite, PointHasher> hashedSites;
	
	for (VoronoiSite& site : sites) {
		hashedSites.insert(std::pair<Point, VoronoiSite>(site.position(), site));
	}
	
	sites.clear();
	
	for (std::pair<Point, VoronoiSite> pair : hashedSites) {
		sites.push_back(pair.second);
	}
}
