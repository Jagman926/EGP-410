#ifndef GRID_GRAPH
#define GRID_GRAPH

#include "Graph.h"

class Grid;

class GridGraph : public Graph
{
public:
	GridGraph(Grid* pGrid);
	virtual ~GridGraph();

	void setGrid(Grid* pGrid) { mpGrid = pGrid; };
	void init();

private:
	Grid* mpGrid;
};


#endif // !GRID_GRAPH