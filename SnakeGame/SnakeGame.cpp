#include "raylib.h"
#include <vector>
#include <map>
#include <string>

const int screenWidth = 800;
const int screenHeight = 450;

const int blockSize = 50;

class Snake
{
public:
	Vector2 frontPosition;
	std::map<std::string, Vector2> directions;
	std::string currentDirection;
};

Snake snake;

void InitGame();
void DrawGame();

int main(void)
{
	InitWindow(screenWidth, screenHeight, "Snake Game");

	InitGame();

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
			
			DrawGame();

		EndDrawing();
	}


	CloseWindow();

	return 0;
}

void InitGame()
{
	Vector2 left = { -50, 0 };
	Vector2 right = { 50, 0 };
	Vector2 up = { 0, -50 };
	Vector2 down = { 0, 50 };

	snake.directions["LEFT"] = left;
	snake.directions["RIGHT"] = right;
	snake.directions["UP"] = up;
	snake.directions["DOWN"] = down;

	snake.frontPosition.x = (screenWidth / 2) - (blockSize / 2);
	snake.frontPosition.y = (screenHeight / 2) - (blockSize / 2);
}

void DrawGame()
{
	ClearBackground(RAYWHITE);

	DrawRectangle(snake.frontPosition.x, snake.frontPosition.y, blockSize, blockSize, LIGHTGRAY);

	if (IsKeyPressed('W')) snake.currentDirection = "UP";
	else if (IsKeyPressed('A')) snake.currentDirection = "LEFT";
	else if (IsKeyPressed('S')) snake.currentDirection = "DOWN";
	else if (IsKeyPressed('D')) snake.currentDirection = "RIGHT";

	snake.frontPosition.x += snake.directions[snake.currentDirection].x;
	snake.frontPosition.y += snake.directions[snake.currentDirection].y;

	WaitTime(0.5);
}
