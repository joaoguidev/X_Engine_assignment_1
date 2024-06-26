#include "TileMap.h"
#include <stdio.h>
#include <iostream>

using namespace AI;

namespace
{
	inline int ToIndex(int x, int y, int columns)
	{
		return x + (y * columns);
	}
	const float tileSize = 32.0f;
}

void TileMap::LoadTiles(const char* fileName)
{
	// Done - Read the provided file and populate mTiles here

	mTiles.clear();
	FILE* file = nullptr;
	fopen_s(&file, fileName, "r");

	int count = 0;
	int isBlocked = 0;

	fscanf_s(file, "Tiles: %d\n", &count);


	for (int j = 0; j < count; j++)
	{
		char buffer[512];
		fscanf_s(file, "%s", buffer, static_cast<int>(std::size(buffer)));
		mTiles.push_back(X::LoadTexture(buffer));
		fscanf_s(file, " %i\n", &isBlocked);
		mBlocked.push_back(isBlocked);
	}

	fclose(file);
	mTileWidth = X::GetSpriteWidth(mTiles.front());
	mTileHeight = X::GetSpriteHeight(mTiles.front());
}

void TileMap::LoadMap(const char* fileName)
{
	// Done - Read the provided file and populate mMap here
	FILE* file = nullptr;
	fopen_s(&file, fileName, "r");
	if (!fopen_s)
	{
		std::cout << "Could not read file";
		exit(101);
	}

	fscanf_s(file, "Columns: %d\n", &mColumns);
	fscanf_s(file, "Rows: %d\n", &mRows);

	mMap.reserve(mColumns * mRows);
	for (int y = 0; y < mRows; y++)
	{
		for (int x = 0; x < mColumns; x++)
		{
			const int index = GetIndex(x, y);
			mMap.push_back(fgetc(file) - '0');

		}
		fgetc(file);
	}

	fclose(file);


	

	// Done - Initialize graph
	mGraph.Initialize(mColumns, mRows);
	for (int r = 0; r < mRows; r++)
	{
		for (int c = 0;  c < mColumns; c++)
		{
			//**********************************REMEMBER************************
			//======================== REFACTOR HERE!!!!!!!!!!!!!!!!! ===================
			if (!IsBlocked(c, r))
			{
				//North
				if (r - 1 < 0) {
					mGraph.GetNode(c, r)->neighbors[GridBasedGraph::North] = nullptr;
				}
				else {
					if (!IsBlocked(c, r - 1)) {
						mGraph.GetNode(c, r)->neighbors[GridBasedGraph::North] = mGraph.GetNode(c, r - 1);
					}
				}

				//NorthWest
				if (c - 1 < 0 || r - 1 < 0) {
					mGraph.GetNode(c, r)->neighbors[GridBasedGraph::NorthWest] = nullptr;
				}
				else {
					if (!IsBlocked(c - 1, r - 1)) {
						mGraph.GetNode(c, r)->neighbors[GridBasedGraph::NorthWest] = mGraph.GetNode(c - 1, r - 1);
					}

				}

				//West
				if (c - 1 < 0) {
					mGraph.GetNode(c, r)->neighbors[GridBasedGraph::West] = nullptr;
				}
				else {

					if (!IsBlocked(c - 1, r)) {
						mGraph.GetNode(c, r)->neighbors[GridBasedGraph::West] = mGraph.GetNode(c - 1, r);
					}
				}

				//SouthWest
				if (c - 1 < 0 || r + 1 >= mRows) {
					mGraph.GetNode(c, r)->neighbors[GridBasedGraph::SouthWest] = nullptr;
				}
				else {

					if (!IsBlocked(c - 1, r + 1)) {
						mGraph.GetNode(c, r)->neighbors[GridBasedGraph::SouthWest] = mGraph.GetNode(c - 1, r + 1);
					}
				}

				//South
				if (r + 1 >= mRows) {
					mGraph.GetNode(c, r)->neighbors[GridBasedGraph::South] = nullptr;
				}
				else {

					if (!IsBlocked(c, r + 1)) {
						mGraph.GetNode(c, r)->neighbors[GridBasedGraph::South] = mGraph.GetNode(c, r + 1);
					}
				}

				//SouthEast
				if (c + 1 >= mColumns || r + 1 >= mRows) {
					mGraph.GetNode(c, r)->neighbors[GridBasedGraph::SouthEast] = nullptr;
				}
				else {

					if (!IsBlocked(c + 1, r + 1)) {
						mGraph.GetNode(c, r)->neighbors[GridBasedGraph::SouthEast] = mGraph.GetNode(c + 1, r + 1);
					}
				}

				//East
				if (c + 1 >= mColumns) {
					mGraph.GetNode(c, r)->neighbors[GridBasedGraph::East] = nullptr;
				}
				else {

					if (!IsBlocked(c + 1, r)) {
						mGraph.GetNode(c, r)->neighbors[GridBasedGraph::East] = mGraph.GetNode(c + 1, r);
					}
				}

				//NorthEast
				if (c + 1 >= mColumns || r - 1 < 0) {
					mGraph.GetNode(c, r)->neighbors[GridBasedGraph::NorthEast] = nullptr;
				}
				else {

					if (!IsBlocked(c + 1, r - 1)) {
						mGraph.GetNode(c, r)->neighbors[GridBasedGraph::NorthEast] = mGraph.GetNode(c + 1, r - 1);
					}
				}
			}

		}
	}
	//     // connect nodes to it's neighbors
	// mGraph.GetNode(4, 5)->neighbors[GridBasedGraph::East] = mGraph.GetNode(5, 5);

// Read the provided file and populate mMap here

}

void TileMap::Render() const
{

	// TODO - Draw the map using mTiles and mMap
	int offSet = tileSize / 2;
	// TODO - Use X::DrawScreenLine to visualize the graph
	//X::DrawScreenLine
	for (int r = 0; r < mRows; r++)
	{
		for (int c = 0; c < mColumns; c++)
		{
			GridBasedGraph::Node const *current  = mGraph.GetNode(c, r);
			if (mGraph.GetNode(c, r)->neighbors[GridBasedGraph::North] != nullptr)
			{
				X::DrawScreenLine(current->columns * tileSize + offSet, current->row * tileSize + offSet, current->neighbors[GridBasedGraph::North]->columns * tileSize + offSet, current->neighbors[GridBasedGraph::North]->row * tileSize + offSet, X::Colors::Orange);
			}
			if (mGraph.GetNode(c, r)->neighbors[GridBasedGraph::NorthEast] != nullptr)
			{
				X::DrawScreenLine(current->columns * tileSize + offSet, current->row * tileSize + offSet, current->neighbors[GridBasedGraph::NorthEast]->columns * tileSize + offSet, current->neighbors[GridBasedGraph::NorthEast]->row * tileSize + offSet, X::Colors::Orange);
			}
			if (mGraph.GetNode(c, r)->neighbors[GridBasedGraph::East] != nullptr)
			{
				X::DrawScreenLine(current->columns * tileSize + offSet, current->row * tileSize + offSet, current->neighbors[GridBasedGraph::East]->columns * tileSize + offSet, current->neighbors[GridBasedGraph::East]->row * tileSize + offSet, X::Colors::Orange);
			}
			if (mGraph.GetNode(c, r)->neighbors[GridBasedGraph::SouthEast] != nullptr)
			{
				X::DrawScreenLine(current->columns * tileSize + offSet, current->row * tileSize + offSet, current->neighbors[GridBasedGraph::SouthEast]->columns * tileSize + offSet, current->neighbors[GridBasedGraph::SouthEast]->row * tileSize + offSet, X::Colors::Orange);
			}
			if (mGraph.GetNode(c, r)->neighbors[GridBasedGraph::South] != nullptr)
			{
				X::DrawScreenLine(current->columns * tileSize + offSet, current->row * tileSize + offSet, current->neighbors[GridBasedGraph::South]->columns * tileSize + offSet, current->neighbors[GridBasedGraph::South]->row * tileSize + offSet, X::Colors::Orange);
			}
			if (mGraph.GetNode(c, r)->neighbors[GridBasedGraph::SouthWest] != nullptr)
			{
				X::DrawScreenLine(current->columns * tileSize + offSet, current->row * tileSize + offSet, current->neighbors[GridBasedGraph::SouthWest]->columns * tileSize + offSet, current->neighbors[GridBasedGraph::SouthWest]->row * tileSize + offSet, X::Colors::Orange);
			}
			if (mGraph.GetNode(c, r)->neighbors[GridBasedGraph::West] != nullptr)
			{
				X::DrawScreenLine(current->columns * tileSize + offSet, current->row * tileSize + offSet, current->neighbors[GridBasedGraph::West]->columns * tileSize + offSet, current->neighbors[GridBasedGraph::West]->row * tileSize + offSet, X::Colors::Orange);
			}
			if (mGraph.GetNode(c, r)->neighbors[GridBasedGraph::NorthWest] != nullptr)
			{
				X::DrawScreenLine(current->columns * tileSize + offSet, current->row * tileSize + offSet, current->neighbors[GridBasedGraph::NorthWest]->columns * tileSize + offSet, current->neighbors[GridBasedGraph::NorthWest]->row * tileSize + offSet, X::Colors::Orange);
			}
		}







	}
	//Draw the map using mTiles and mMap
	for (int y = 0; y < mRows ; y++)
	{
		for (int x = 0; x < mColumns; x++)
		{
			const int mapIndex = GetIndex(x, y);
			const int tileIndex = mMap[mapIndex];
			const X::TextureId textureId = mTiles.at(tileIndex);
			X::DrawSprite(textureId, {x * tileSize, y * tileSize} , X::Pivot::TopLeft);
		}
	}

	//Draw ClosedList
	for (auto& node : mClosedList)
	{
		auto parent = node->parent;
		if (parent != nullptr)
		{
			const auto a = GetPixelPosition(node->columns, node->row);
			const auto b = GetPixelPosition(parent->columns, parent->row);
			X::DrawScreenLine(a, b, X::Colors::Red);
		}
	}

}

// 2D map - 5 columns x 4 rows
// [0][0][0][0][0]
// [0][0][0][0][0]
// [0][0][0][X][0]   X is at (3, 2)
// [0][0][0][0][0]

// Stored as 1D - 5x4 = 20 slots
// [0][0][0][0][0] [0][0][0][0][0] [0][0][0][X][0] [0][0][0][0][0]
//
// index = column + (row * columnCount)
//       = 3 + (2 * 5)
//       = 13

int TileMap::GetIndex(int column, int row) const
{
	return column + (row * mColumns);
}


bool TileMap::IsBlocked(int x, int y) const
{
	const int tile = mMap[ToIndex(x, y, mColumns)];
	const bool blocked = mBlocked[tile];
	return blocked;
}	

std::vector<X::Math::Vector2> TileMap::FindPathBFS(int startX, int startY, int endX, int endY)
{
	std::vector<X::Math::Vector2> path;

	BFS bfs;
	if (bfs.Run(mGraph, startX, startY, endX, endY))
	{
		const auto& closedList = bfs.GetClosedList();
		auto node = closedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->columns, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());

		// Cache the closed list for visualization
		mClosedList = closedList;
	}

	return path;
}

std::vector<X::Math::Vector2> TileMap::FindPathDFS(int startX, int startY, int endX, int endY)
{
	std::vector<X::Math::Vector2> path;

	DFS dfs;
	if (dfs.Run(mGraph, startX, startY, endX, endY))
	{
		const auto& closedList = dfs.GetClosedList();
		auto node = closedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->columns, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());

		// Cache the closed list for visualization
		mClosedList = closedList;
	}

	return path;
}

std::vector<X::Math::Vector2> TileMap::FindPathDijkstra(int startX, int startY, int endX, int endY)
{
	std::vector<X::Math::Vector2> path;

	auto getCostWrapper = [&](auto nodeA, auto nodeB)
	{
		return GetCost(nodeA, nodeB);
	};

	Dijkstra dijkstra;
	if (dijkstra.Run(mGraph, startX, startY, endX, endY, getCostWrapper))
	{
		const auto& closedList = dijkstra.GetClosedList();
		auto node = closedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->columns, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());

		// Cache the closed list for visualization
		mClosedList = closedList;
	}

	return path;
}

std::vector<X::Math::Vector2> TileMap::FindPathASearch(int startX, int startY, int endX, int endY)
{
	std::vector<X::Math::Vector2> path;

	auto getCostWrapper = [&](auto nodeA, auto nodeB)
	{
		return GetCost(nodeA, nodeB);
	};

	ASearch aSearch;
	if (aSearch.Run(mGraph, startX, startY, endX, endY, getCostWrapper))
	{
		const auto& closedList = aSearch.GetClosedList();
		auto node = closedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->columns, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());

		// Cache the closed list for visualization
		mClosedList = closedList;
	}

	return path;
}

X::Math::Vector2 TileMap::GetPixelPosition(int x, int y) const
{
	return {
		(x + 0.5f) * mTileWidth,
		(y + 0.5f) * mTileHeight,
	};
}

float TileMap::GetCost(const AI::GridBasedGraph::Node* nodeA, const AI::GridBasedGraph::Node* nodeB) const
{
	const int fromTileIndex = ToIndex(nodeA->columns, nodeA->row, mColumns);
	const int toTileIndex = ToIndex(nodeB->columns, nodeB->row, mColumns);
	const int tileType = mMap[toTileIndex];
	if (tileType == 1)
	{
		return 5.0f;
	}
	else
	{
		return 1.0f;
	}
}