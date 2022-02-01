#include "Precompiled.h"
#include "ASearch.h"

using namespace AI;
namespace
{
	inline int EuclideanDistance(GridBasedGraph::Node* node, int endX, int endY)
	{
		return static_cast<int>( sqrt(pow(endX - node->columns, 2) +
			pow(endY - node->row, 2) * 1.0));
	}
}

bool ASearch::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost)
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
		auto node = mOpenList.front();
		mOpenList.pop_front();
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
				if (neighbor == nullptr)
				{
					continue;
				}

				if (!neighbor->opened)
				{
					mOpenList.push_back(neighbor);
					neighbor->opened = true;
					neighbor->parent = node;
					neighbor->h = EuclideanDistance(neighbor, endX, endY);
					neighbor->g = node->g + getCost(node, neighbor) + neighbor->h;

				}
				auto comparator = [](GridBasedGraph::Node* f, GridBasedGraph::Node* s) { return f->g < s->g; };
				/*mOpenList.sort(compareNodes);*/
				mOpenList.sort(comparator); // Better way!
			}
		}

		//		Add node N to closed list
		mClosedList.push_back(node);
		node->closed = true;
	}
	return found;
}


