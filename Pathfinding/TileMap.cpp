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

	fscanf_s(file, "Tiles: %d\n", &count);


	for (int i = 0; i < count; i++)
	{
		char buffer[512];
		fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));
		mTiles.push_back(X::LoadTexture(buffer));

	}

	fclose(file);

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
			//North
			if (r - 1 < 0) {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::North] = nullptr;
			}
			else {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::North] = mGraph.GetNode(c, r - 1);
			}

			//NorthWest
			if (  c - 1 < 0 || r - 1 < 0) {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::NorthWest] = nullptr;
			}
			else {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::NorthWest] = mGraph.GetNode(c - 1, r - 1);
			}

			//West
			if (c - 1 < 0) {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::West] = nullptr;
			}
			else {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::West] = mGraph.GetNode(c - 1, r);
			}

			//SouthWest
			if ( c - 1 < 0 || r + 1 >= mRows) {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::SouthWest] = nullptr;
			}
			else {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::SouthWest] = mGraph.GetNode(c - 1, r + 1);
			}

			//South
			if (r + 1 >= mRows) {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::South] = nullptr;
			}
			else {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::South] = mGraph.GetNode(c, r + 1);
			}

			//SouthEast
			if (c + 1 >= mColumns || r + 1 >= mRows) {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::SouthEast] = nullptr;
			}
			else {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::SouthEast] = mGraph.GetNode(c + 1, r + 1);
			}

			//East
			if (c + 1 >= mColumns) {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::East] = nullptr;
			}
			else {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::East] = mGraph.GetNode(c + 1, r);
			}

			//NorthEast
			if (c + 1 >= mColumns || r - 1 < 0) {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::NorthEast] = nullptr;
			}
			else {
				mGraph.GetNode(c, r)->neighbors[GridBasedGraph::NorthEast] = mGraph.GetNode(c + 1, r - 1);
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

	// TODO - Use X::DrawScreenLine to visualize the graph
	//X::DrawScreenLine




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