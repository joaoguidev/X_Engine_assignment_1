#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;

void GridBasedGraph::Initialize(int columns, int rows)
{
	mColumns = columns;
	mRows = rows;
	// Done
	// Resize mNodes to the matching dimension
	mNodes.clear();
	mNodes.reserve(mColumns * mRows);
	
	// For each node, set it's attributes (row/column)
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			GridBasedGraph::Node* newNode = new Node();
			newNode->columns = c;
			newNode->row = r;
			mNodes.push_back(*newNode);
		}
	}
	// However, the connection is up to the user


}

void AI::GridBasedGraph::ResetSearchParams()
{
	for (auto& node: mNodes)
	{
		node.parent = nullptr;
		node.opened = false;
		node.closed = false;
		node.g = 0.0f;
		node.h = 0.0f;
	}
}

GridBasedGraph::Node* GridBasedGraph::GetNode(int column, int row)
{
	// Done
	if (column < 0 || column >= mColumns || row < 0 || row >= mRows)
	{
		return nullptr;
	}
	return &mNodes[GetIndex(column, row)];
}

const GridBasedGraph::Node* GridBasedGraph::GetNode(int column, int row) const
{
	// Done
	if (column < 0 || column >= mColumns || row < 0 || row >= mRows)
	{
		return nullptr;
	}
	return &mNodes[GetIndex(column, row)] ;
}

int GridBasedGraph::GetIndex(int column, int row) const
{
	// Done+

	return column + (row * mColumns);
}