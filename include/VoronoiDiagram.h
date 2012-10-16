#pragma once

#include <vector>
#include <map>
#include <memory>

#include <VoronoiSite.h>
#include <VoronoiEdge.h>
#include <VoronoiCell.h>

namespace voronoi {

class VoronoiDiagram
{
public:
	VoronoiDiagram();

	static VoronoiDiagram create(const std::vector<VoronoiSite>& sites);
	static void removeDuplicates(std::vector<VoronoiSite>& sites);

	const std::vector<VoronoiSite>& sites() const;
	std::vector<VoronoiSite>& sites();
	const std::vector<VoronoiEdge*>& edges() const;
	std::vector<VoronoiEdge*>& edges();
	const std::map<VoronoiSite*, VoronoiCell*>& cells() const;
	std::map<VoronoiSite*, VoronoiCell*>& cells();

	void clear();
	void initialize(const std::vector<VoronoiSite>& sites);
	void calculate();
	VoronoiEdge* createEdge(VoronoiSite* left, VoronoiSite* right);
protected:
	struct Data
	{
		~Data();
		
		std::vector<VoronoiSite> sites;
		std::vector<VoronoiEdge*> edges;
		std::map<VoronoiSite*, VoronoiCell*> cells;
	};
	
	std::shared_ptr<Data> data;
};

} //end namespace voronoi

