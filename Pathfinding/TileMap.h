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
	std::vector<X::Math::Vector2> FindPathBFS(int startX, int startY, int endX, int endY);
	X::Math::Vector2 GetPixelPosition(int x, int y) const;

private:
	AI::NodeList mClosedList;
	AI::GridBasedGraph mGraph;
	std::vector<int> mMap;
	std::vector<X::TextureId> mTiles; // I forgot to add this in class
	std::vector<bool> mBlocked;
	int mColumns = 0;
	int mRows = 0;
	int mTileWidth = 0;
	int mTileHeight = 0;

};