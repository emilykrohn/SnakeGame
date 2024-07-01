#include "raylib.h"
#include <vector>
#include <array>
#include <map>
#include <string>
#include <cstdlib>
#include <time.h>

const int screenWidth = 750;
const int screenHeight = 450;

const int blockSize = 50;

float timer = 0;

class Snake
{
public:
	Vector2 frontPosition = { 0, 0 };

	std::map<std::string, Vector2> directions;
	std::string currentDirection = "RIGHT";

	std::vector<Vector2> positions;
	int blockCounter = 0;

	float delayInSeconds = 0.5;
};

class Apple
{
public:
	Vector2 position = { 0,0 };
	bool isOnScreen = false;
};

Snake snake;
Apple apple;

void InitGame();
void DrawGame();
void DrawApple();

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

	snake.positions.push_back(snake.frontPosition);
	snake.blockCounter++;

	srand(time(0));
}

void DrawGame()
{
	ClearBackground(RAYWHITE);

	if (IsKeyPressed('W')) snake.currentDirection = "UP";
	else if (IsKeyPressed('A')) snake.currentDirection = "LEFT";
	else if (IsKeyPressed('S')) snake.currentDirection = "DOWN";
	else if (IsKeyPressed('D')) snake.currentDirection = "RIGHT";

	timer += GetFrameTime();

	if (timer > snake.delayInSeconds)
	{
		snake.frontPosition.x += snake.directions[snake.currentDirection].x;
		snake.frontPosition.y += snake.directions[snake.currentDirection].y;

		timer = 0;
	}

	DrawRectangle(snake.frontPosition.x, snake.frontPosition.y, blockSize, blockSize, LIGHTGRAY);

	DrawApple();
}

void DrawApple()
{
	if (!apple.isOnScreen)
	{
		bool isPositionUpdated = false;

		while (!isPositionUpdated)
		{
			int tempXPosition = rand();
			int tempYPosition = rand();

			for (int i = 0; i < snake.positions.size(); i++)
			{
				if (snake.positions[i].x == tempXPosition || snake.positions[i].y == tempYPosition)
				{
					break;
				}
				else if (i == snake.positions.size())
				{
					apple.position.x = tempXPosition;
					apple.position.y = tempYPosition;
					
					isPositionUpdated = true;
				}
			}
		}

		apple.isOnScreen = true;
	}

	DrawRectangle(apple.position.x, apple.position.y, blockSize, blockSize, RED);
}

