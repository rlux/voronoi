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
