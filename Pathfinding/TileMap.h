#pragma once

#include <AI.h>
#include <XEngine.h>

class TileMap
{
public:
	void LoadTiles(const char* fileName);
	void LoadMap(const char* fileName);

	void Render() const;
	int GetIndex(int column, int row) const;
	bool IsBlocked(int x, int y) const;

private:
	AI::GridBasedGraph mGraph;
	std::vector<int> mMap;
	std::vector<X::TextureId> mTiles; // I forgot to add this in class
	std::vector<bool> mBlocked;
	int mColumns = 0;
	int mRows = 0;
};