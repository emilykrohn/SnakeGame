#include "raylib.h"
#include <vector>

const int screenWidth = 800;
const int screenHeight = 450;

const int blockSize = 50;

class Snake
{
public:
	Vector2 frontPosition;
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
	snake.frontPosition.x = (screenWidth / 2) - (blockSize / 2);
	snake.frontPosition.y = (screenHeight / 2) - (blockSize / 2);
}

void DrawGame()
{
	ClearBackground(RAYWHITE);

	DrawRectangle(snake.frontPosition.x, snake.frontPosition.y, blockSize, blockSize, LIGHTGRAY);
	snake.frontPosition.x += 50;

	WaitTime(0.5);
}
