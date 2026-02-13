#pragma once
#include"Stack.h"

#define X_SIZE 15
#define Y_SIZE 12
using namespace std;

int maze[Y_SIZE][X_SIZE]
= {
	{0,1,0,0,0,1,1,0,0,0,1,1,1,1,1},
	{1,0,0,0,1,1,0,1,1,1,0,0,1,1,1},
	{0,1,1,0,0,0,0,1,1,1,1,0,0,1,1},
	{1,1,0,1,1,1,1,0,1,1,0,1,1,0,0},
	{1,1,0,1,0,0,1,0,1,1,1,1,1,1,1},
	{0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},
	{0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},
	{0,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
	{0,0,1,1,0,1,1,0,1,1,1,1,1,0,1},
	{1,1,0,0,0,1,1,0,1,1,0,0,0,0,0},
	{0,0,1,1,1,1,1,0,0,0,1,1,1,1,0},
	{0,1,0,0,1,1,1,1,1,0,1,1,1,1,0}
};

int dirX[8] = { -1,0,1,1,1,0,-1,-1 };
int dirY[8] = { -1,-1,-1,0,1,1,1,0 };

int** ArrayExtender(int arr[Y_SIZE][X_SIZE], int& xSize, int& ySize)
{
	//¿Ü°û -1 Ã³¸®.
	xSize += 2;
	ySize += 2;
	int** ret = new int* [ySize];
	for (int i = 0; i < ySize; i++)
	{
		ret[i] = new int[xSize];
	}
	fill_n(ret[0], xSize, -1);
	fill_n(ret[ySize - 1], xSize, -1);
	for (int i = 1; i < ySize - 1; i++)
	{
		ret[i][0] = -1;
		ret[i][xSize - 1] = -1;
	}

	for (int i = 0; i < ySize - 2; i++)
	{
		for (int j = 0; j < xSize - 2; j++)
		{
			ret[i + 1][j + 1] = arr[i][j];
		}
	}
	return ret;
}

void PrintArr2d(int** arr, int xSize, int ySize)
{
	for (int i = 0; i < ySize; i++)
	{
		for (int j = 0; j < xSize; j++)
		{
			cout.width(3);
			if (arr[i][j] == 1)
			{
				cout << "¡á" << " ";
			}
			else if (arr[i][j] == 2)
			{
				cout << "¡Ù" << " ";
			}
			else if (arr[i][j] == 0)
			{
				cout << "¡à" << " ";
			}
		}
		cout << endl << endl;
	}
}

struct Position
{
	int x, y;

	bool operator==(const Position& right) const
	{
		return x == right.x && y == right.y;
	}
	friend ostream& operator<<(ostream& os, const Position& pos)
	{
		os << "(" << pos.x << ", " << pos.y << ")";
		return os;
	}
};

struct PathElement
{
	friend ostream& operator<<(ostream& os, const PathElement& pathElement)
	{
		os << "[" << pathElement.pos.x << "," << pathElement.pos.y << "]";
		os << " | dir: " << pathElement.dir << endl;
		return os;
	}
	Position pos;
	int dir;
};


int mark[Y_SIZE][X_SIZE] = {};

enum DIR { NW, N, NE, E, SE, S, SW, W };
/*
int dirX[8] = { -1,0,1,1,1,0,-1,-1 };
int dirY[8] = { -1,-1,-1,0,1,1,1,0 };*/

Stack<PathElement> FindPath(int** maze, Position start, Position End)
{
	Stack<PathElement> stack;

	PathElement startPath;
	startPath.pos = start;
	startPath.dir = NW;
	stack.Push(startPath);
	mark[start.y][start.x] = 1;
	int dir;

	while (!stack.IsEmpty())
	{
		Position nowPosition = stack.Top().pos;
		dir = stack.Top().dir;
		stack.Pop();
		mark[nowPosition.y][nowPosition.x] = 1;
		

		while (dir < 8)
		{
			if (nowPosition == End)
			{

			}
			int nextX = nowPosition.x + dirX[dir];
			int nextY = nowPosition.y + dirY[dir];
			if (!maze[nextY][nextX] && !mark[nextY][nextX])
			{
				mark[nextY][nextX] = 1;
				PathElement nowStep;
				nowStep.pos = nowPosition;
				nowStep.dir = dir;
				stack.Push(nowStep);
				nowPosition = Position(nextX, nextY);
				dir = NW;
			}
			
		}

	}

	return stack;
}



int main() {
	int xSize = X_SIZE;
	int ySize = Y_SIZE;
	int** extendedMaze = ArrayExtender(maze, xSize, ySize);
	cout << endl;

	Position start = Position(1, 1);
	Position end = Position(xSize - 2, ySize - 2);

	Stack<PathElement> pathStack = FindPath(extendedMaze, start, end);

	PrintArr2d(extendedMaze, xSize, ySize);

	cout << pathStack << endl;
}
