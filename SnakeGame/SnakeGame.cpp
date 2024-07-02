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

	float delayInSeconds = 0.5;
};

class Apple
{
public:
	Vector2 position = { 0,0 };
};

Snake snake;
Apple apple;

void InitGame();
void DrawGame();

void PlayerInput();
void DrawApple();
void DrawSnake();
void SnakeMovement();
void UpdateSnakePosition();
void SpawnApple();
Vector2 GenerateRandomPosition();
void AppleCollision();
bool isValidPosition(Vector2 position);
void AddSnakeBlock();

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

	SpawnApple();

	srand(time(0));
}

void DrawGame()
{
	ClearBackground(RAYWHITE);

	PlayerInput();

	SnakeMovement();

	DrawApple();

	DrawSnake();

	AppleCollision();
}

void DrawSnake()
{
	for (int i = 0; i < snake.positions.size(); i++)
	{
		DrawRectangle(snake.positions[i].x, snake.positions[i].y, blockSize, blockSize, LIGHTGRAY);
	}
}

void PlayerInput()
{
	if (IsKeyPressed('W') && snake.currentDirection != "DOWN") snake.currentDirection = "UP";
	else if (IsKeyPressed('A') && snake.currentDirection != "RIGHT") snake.currentDirection = "LEFT";
	else if (IsKeyPressed('S') && snake.currentDirection != "UP") snake.currentDirection = "DOWN";
	else if (IsKeyPressed('D') && snake.currentDirection != "LEFT") snake.currentDirection = "RIGHT";
}

void UpdateSnakePosition()
{
	for (int i = snake.positions.size() - 1; i > 0; i--)
	{
		snake.positions[i] = snake.positions[i - 1];
	}

	snake.positions[0] = snake.frontPosition;
}

void SnakeMovement()
{
	timer += GetFrameTime();

	if (timer > snake.delayInSeconds)
	{
		snake.frontPosition.x += snake.directions[snake.currentDirection].x;
		snake.frontPosition.y += snake.directions[snake.currentDirection].y;

		UpdateSnakePosition();

		timer = 0;
	}
}

void DrawApple()
{
	DrawRectangle(apple.position.x, apple.position.y, blockSize, blockSize, RED);
}

void SpawnApple()
{
	bool isPositionUpdated = false;

	while (!isPositionUpdated)
	{
		Vector2 tempPosition = GenerateRandomPosition();

		if (isValidPosition(tempPosition))
		{
			apple.position.x = tempPosition.x;
			apple.position.y = tempPosition.y;
					
			isPositionUpdated = true;
		}
	}
}

Vector2 GenerateRandomPosition()
{
	Vector2 position;

	position.x = rand() % 8 * 100;
	if (position.x != 700 && rand() % 2) position.x += 50;

	position.y = rand() % 5 * 100;
	if (position.y != 400 && rand() % 2) position.y += 50;

	return position;
}

bool isValidPosition(Vector2 position)
{
	for (int i = 0; i < snake.positions.size(); i++)
	{
		if (snake.positions[i].x == position.x && snake.positions[i].y == position.y)
		{
			return false;
		}
	}
	return true;
}

void AddSnakeBlock()
{
	Vector2 newBlockPosition = snake.positions[snake.positions.size() - 1];
	snake.positions.push_back(newBlockPosition);
}

void AppleCollision()
{
	if (snake.frontPosition.x == apple.position.x && snake.frontPosition.y == apple.position.y)
	{
		SpawnApple();
		AddSnakeBlock();
	}
}

