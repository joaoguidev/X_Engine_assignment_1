#include "TileMap.h"
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <iostream>
TileMap tileMap;
X::TextureId textureId;
X::Math::Vector2 position;
X::Math::Vector2 mouseClick;
int startX = 8;
int startY = 4;
int endX = 20;
int endY = 15;

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
	mouseClick = X::Math::Vector2(X::GetMouseScreenX(), X::GetMouseScreenY());
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

	X::DrawSprite(textureId, position, X::Pivot::TopLeft, X::Flip::Horizontal);
	X::DrawScreenDiamond(position, 5.0f, X::Colors::Cyan);

	//auto path = tileMap.FindPathBFS(position.x,position.y, mouseClick.x, mouseClick.y);
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		path = tileMap.FindPathBFS(startX,startY,endX,endY);
	}

	for (int i = 0; i + 1 < path.size(); ++i)
	{
		const auto a = path[i];	
		const auto b = path[i + 1];
		X::DrawScreenLine(a, b, X::Colors::AliceBlue);
	}
		
	X::DrawScreenCircle(tileMap.GetPixelPosition(startX,startY), 10.0f, X::Colors::Aquamarine);
	X::DrawScreenCircle(tileMap.GetPixelPosition(endX, endY), 10.0f, X::Colors::BlueViolet);

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