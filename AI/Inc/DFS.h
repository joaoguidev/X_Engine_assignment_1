#pragma once

#include "GridBasedGraph.h"
#include <list>

namespace AI
{
	using NodeList = std::list<GridBasedGraph::Node*>;

	class DFS
	{
	public:
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY);

		const NodeList& GetClosedList() const { return mClosedList; }

	private:
		NodeList mOpenList;
		NodeList mClosedList;
	};
}
