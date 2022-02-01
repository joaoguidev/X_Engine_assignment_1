#include "TileMap.h"
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <iostream>
TileMap tileMap;
X::TextureId textureId;
X::Math::Vector2 position;
X::Math::Vector2 mousePosition;
int startX = 8;
int startY = 4;
int endX = 20;
int endY = 15;
int mTileWidth = 32;
int mTileHeight = 32;

std::vector<X::Math::Vector2> path;
//--------------------------------------------------

void GameInit()
{
	tileMap.LoadTiles("tiles.txt");
	tileMap.LoadMap("map.txt");

	textureId = X::LoadTexture("bird1.png");
	position = { 100.0f, 100.0f };
}

bool GameLoop(float deltaTime)
{
	mousePosition = X::Math::Vector2(X::GetMouseScreenX()/ mTileWidth, X::GetMouseScreenY()/ mTileHeight);
	const float moveSpeed = 200.0f; // pixel per second
	if (X::IsKeyDown(X::Keys::RIGHT))
		position.x += moveSpeed * deltaTime;
	if (X::IsKeyDown(X::Keys::DOWN))
		position.y += moveSpeed * deltaTime;
	if (X::IsKeyDown(X::Keys::LEFT))
		position.x -= moveSpeed * deltaTime;
	if (X::IsKeyDown(X::Keys::UP))
		position.y -= moveSpeed * deltaTime;

	tileMap.Render();

		endX = X::GetMouseScreenX() / mTileWidth;
		endY = X::GetMouseScreenY() / mTileHeight;

		X::DrawScreenDiamond(position, 10.0f, X::Colors::Black);

	//X::DrawSprite(textureId, position, X::Pivot::TopLeft, X::Flip::Horizontal);
	X::DrawScreenDiamond(position, 10.0f, X::Colors::Cyan);

	if (X::IsKeyPressed(X::Keys::ONE))
	{
		path = tileMap.FindPathBFS(startX,startY,endX,endY);
	}
	if (X::IsKeyPressed(X::Keys::TWO))
	{
		path = tileMap.FindPathDFS(startX, startY, endX, endY);
	}
	if (X::IsKeyDown(X::Keys::THREE))
	{
		path = tileMap.FindPathDijkstra(startX, startY, endX, endY);
	}


	for (int i = 0; i + 1 < path.size(); ++i)
	{
		const auto a = path[i];	
		const auto b = path[i + 1];
		X::DrawScreenLine(a, b, X::Colors::AliceBlue);
	}
		
	//X::DrawScreenCircle(tileMap.GetPixelPosition(startX,startY), 10.0f, X::Colors::Aquamarine);
	//X::DrawScreenCircle(tileMap.GetPixelPosition(endX, endY), 10.0f, X::Colors::BlueViolet);

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{

}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Pathfinding");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}