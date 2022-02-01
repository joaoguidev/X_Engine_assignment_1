#include "Precompiled.h"
#include "DFS.h"

using namespace AI;

bool DFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
{
	// Reset everything
	graph.ResetSearchParams();
	mOpenList.clear();
	mClosedList.clear();

	// Add start node to open list
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->opened = true;

	bool found = false;

	// TODO:
	//	while end node not reached && open list isn’t empty:
	while (!found && !mOpenList.empty())
	{
		//select node N from open list <- depend on your strategy
		auto node = mOpenList.back();
		mOpenList.pop_back();
		//		if node is end
		if (node->columns == endX && node->row == endY)
		{
			//		found = true
			found = true;
		}
		else
		{
			//		else expand node N :
			for (auto neighbor : node->neighbors)
			{
				//			if expanded node isn’t in open nor closed lists:
				if (neighbor == nullptr || neighbor->opened)
				{
					continue;
				}
				//		add expanded node to open list, set parent
				mOpenList.push_back(neighbor);
				neighbor->opened = true;
				neighbor->parent = node;
			}
		}

		//		Add node N to closed list
		mClosedList.push_back(node);
		node->closed = true;
	}
	return found;
}

