#include "NodeRecord.h"

void NodeRecord::insert(Node * n, Connection * c, float cost, float estimatedCost)
{
	mNode = n; 
	mConnection = c; 
	mCostSoFar = cost; 
	mEstimatedTotalCost = estimatedCost;
}
