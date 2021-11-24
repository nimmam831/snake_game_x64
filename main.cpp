#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum class eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
void Setup()
{
	gameOver = false;
	dir = eDirecton::STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}

				if (not print)
					cout << " ";

			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = eDirecton::LEFT;
			break;
		case 'd':
			dir = eDirecton::RIGHT;
			break;
		case 'w':
			dir = eDirecton::UP;
			break;
		case 's':
			dir = eDirecton::DOWN;
			break;
		case 'm':
			gameOver = true;
			break;
		case 'A':
			dir = eDirecton::LEFT;
			break;
		case 'D':
			dir = eDirecton::RIGHT;
			break;
		case 'W':
			dir = eDirecton::UP;
			break;
		case 'S':
			dir = eDirecton::DOWN;
			break;
		case 'M':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case eDirecton::LEFT:
		x--;
		break;
	case eDirecton::RIGHT:
		x++;
		break;
	case eDirecton::UP:
		y--;
		break;
	case eDirecton::DOWN:
		y++;
		break;
	default:
		break;
	}


	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= width) y = 0; else if (y < 0) y = height - 1;
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
		{
			nTail--;
			score -= 5;
		}
	if (x == fruitX && y == fruitY)
	{
		score += 5;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	Setup();
	while (not gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);
		if (score < 0)
		{
			gameOver = true;
		}
	}
	return 0;
}
