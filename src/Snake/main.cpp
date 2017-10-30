
#include <queue>
#include <iostream>
#include "../Common/Graphics.h"
#include "../Common/Input.h"
#include "../Common/Time.h"
#include "../Common/Random.h"

typedef struct Coord
{
	int x;
	int y;
	Coord() { x = 0; y = 0; }
	Coord(int x, int y) { this->x = x; this->y = y; }
} Coord;

const int gameSize = 20;
const int cellSize = 8;
float fps = 4;
const int minFps = 4;
const int maxFps = 15;
Timer updateTimer;
Timer gameTimer;

typedef std::deque<Coord> SnakeCoords;
SnakeCoords snake;
const int snakeStartSize = 4;
int dirX, dirY;
int lastDirX, lastDirY;

Coord apple;
Timer appleTimer;
float maxAppleTime = 6;
float lastAppleFlash = 0;
float appleFlashRate = 0.1f;

Colour snakeColour = Colour(0, 0, 1);
Colour appleColour = Colour(1, 0, 0);
Colour normalAppleColour = Colour(1, 0, 0);
Colour bgColour = Colour(1, 1, 1);

void Update(double deltaTime)
{
	if (Key.escape)
		exit(0);
		
	if (Key.up && lastDirY != -1) { dirX = 0; dirY = 1; }
	else if (Key.down && lastDirY != 1) { dirX = 0; dirY = -1; }
	else if (Key.left && lastDirX != 1) { dirX = -1; dirY = 0; }
	else if (Key.right && lastDirX != -1) { dirX = 1; dirY = 0; }
	
	if (appleTimer.ElapsedSeconds() >= maxAppleTime - 1)
	{
		if (appleTimer.ElapsedSeconds() - lastAppleFlash >= appleFlashRate)
		{
			appleColour = (appleColour == normalAppleColour) ? bgColour : normalAppleColour;
			lastAppleFlash = appleTimer.ElapsedSeconds();
		}
	}
	
	if (updateTimer.ElapsedSeconds() >= 1.0f / fps)
	{
		updateTimer.Reset();
			
		Coord next = snake.front();
		next.x += dirX;
		next.y += dirY;
		lastDirX = dirX;
		lastDirY = dirY;
		
		if (next.x < 0) next.x = gameSize - 1;
		else if (next.y < 0) next.y = gameSize - 1;
		else if (next.x >= gameSize) next.x = 0;
		else if (next.y >= gameSize) next.y = 0;
			
		for (SnakeCoords::iterator i = snake.begin(); i != snake.end(); i++)
		{
			if (next.x == i->x && next.y == i->y)
			{
				std::cout << "Game Over [score:" << (snake.size()-snakeStartSize-1) << "; "; 
				std::cout << "time:" << gameTimer.ToString() << "]\n";
				exit(0);
			}
		}
		
		snake.push_front(next);
		
		if (snake.front().x == apple.x && snake.front().y == apple.y || appleTimer.ElapsedSeconds() >= maxAppleTime)
		{
			int rx, ry;
			bool free;
			
			do
			{
				rx = Random::Int(0, gameSize);
				ry = Random::Int(0, gameSize);
				
				free = true;
				for (int i = 0; i < snake.size(); i++)
				{				
					if (snake[i].x == rx && snake[i].y == ry)
					{
						free = false;
						break;
					}
				}
			} while (!free);
			
			apple.x = rx;
			apple.y = ry;
			
			if (appleTimer.ElapsedSeconds() >= maxAppleTime)
				snake.pop_back();
			else
				fps = (minFps + (maxFps - minFps) * (snake.size() / 100.0f));
				
			appleColour = normalAppleColour;
			appleTimer.Reset();
			lastAppleFlash = 0;
		}
		else
		{
			snake.pop_back();
		}
	}
}

void RenderSnakeSegment(int x1, int y1, int x2, int y2) {
	if (x2 == x1) 
	{
		int s = y1 < y2 ? y1 : y2;
		int e = y1 < y2 ? y2 : y1;
		RenderRectangle(x1 * cellSize + 1, s * cellSize + 1, cellSize - 2, cellSize * (e - s + 1) - 2, snakeColour);
	}
	else if (y2 == y1)
	{
		int s = x1 < x2 ? x1 : x2;
		int e = x1 < x2 ? x2 : x1;
		RenderRectangle(s * cellSize + 1, y1 * cellSize + 1, cellSize * (e - s + 1) - 2, cellSize - 2, snakeColour);
	}
}

void Render()
{
	// Render apple
	RenderRectangle(apple.x * cellSize, apple.y * cellSize, cellSize, cellSize, appleColour, bgColour);

	// Render snake
	int index = 0;
	int start = 0;
	while (index < snake.size()) 
	{
		bool turn = snake[index + 1].x != snake[start].x && snake[index + 1].y != snake[start].y;
		bool wrap = abs(snake[index + 1].x - snake[index].x) > 1 || abs(snake[index + 1].y - snake[index].y) > 1;
		if (turn || wrap) {
			RenderSnakeSegment(snake[start].x, snake[start].y, snake[index].x, snake[index].y);
			if (wrap) index++;
			start = index;
		}
		index++;
	}
	RenderSnakeSegment(snake[start].x, snake[start].y, snake[index].x, snake[index].y);
}

int main(int argc, char **argv)
{
	updateTimer.Start();
	gameTimer.Start();
	appleTimer.Start();
	
	for (int i = 0; i < snakeStartSize; i++)
		snake.push_back(Coord(gameSize / 2 - i, gameSize / 2));
	dirX = 1;
	dirY = 0;
	
	apple.x = snake.front().x + 1;
	apple.y = snake.front().y;
	
	InitWindow(gameSize * cellSize, gameSize * cellSize, "Snake", bgColour);
	RunApp(100, Update, Render);
	return 0;
}
