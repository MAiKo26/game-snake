#include <iostream>
#include <conio.h>
#include <Windows.h>
#define KEY_UP 72

#define KEY_DOWN 80

#define KEY_LEFT 75

#define KEY_RIGHT 77
using namespace std;

bool gameOver;
const int width = 55;
const int height = 25;
int x, y, dollarX, dollarY, score;
int tailX[100], tailY[100];
int sTail = 0;
enum Directions { STOP = 0, LEFT, RIGHT, UP, DOWN };
Directions dir;
int sleepLevel, currentLevel;


void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;  // Set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Setup()
{
	gameOver = false;
	dir = STOP;
	srand((unsigned int)time(NULL));
	x = rand() % width;
	y = rand() % height;
	dollarX = rand() % width;
	dollarY = rand() % height;
	score = 0;
	sleepLevel = 5;
	sTail = 0;
	currentLevel = 1;
}

void Draw()
{
	ShowConsoleCursor(false);  // Hide the console cursor

	COORD cursorPos;
	cursorPos.X = 0;
	cursorPos.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);

	
	cout << "            Score: " << score << " || Your Current Level: " << currentLevel <<  endl;

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			bool print = false;

			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "@";
			else if (i == dollarY && j == dollarX)
				if (score == 4 || score == 9 || score == 14 || score == 19 || score == 24 || score == 39)
					cout << "€";
				else
					cout << "$";
			else
			{
							
				for (int k = 0; k < sTail;k++)
				{
					if (tailX[k] == j && tailY[k] == i)
						{
						cout << "=" ;
						print = true;
						}
				}

				if (!print)
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

	
	
	
}



void Input()
{
	if (_kbhit())
	{

		switch (_getch())
		{

		case 'q':
		case KEY_LEFT:
			if (dir == RIGHT && (sTail > 0))
				break;
			dir = LEFT;
			break;
		case 'd':
		case KEY_RIGHT:
			if (dir == LEFT && (sTail > 0))
				break;
			dir = RIGHT;
			break;
		case 's':
		case KEY_DOWN:
			if (dir == UP && (sTail > 0))
				break;
			dir = DOWN;
			break;
		case 'z':
		case KEY_UP:
			if (dir == DOWN && (sTail > 0))
				break;
			dir = UP;
			break;
		case 'x':
			gameOver = true;
			break;



		}
	}

}

void Logic()
{
	
	for (int i = sTail; i > 0; i--)
	{
		tailX[i] = tailX[i - 1];
		tailY[i] = tailY[i - 1];
	}
	tailX[0] = x;
	tailY[0] = y;

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;

	for (int k = 0; k < sTail; k++)
	{
		if ((x == tailX[k]) && (y == tailY[k]))
			gameOver = true;
	}

	if (x == dollarX && y == dollarY)
	{
		sTail++;
		score++ ; 
		dollarX = rand() % width;
		dollarY = rand() % height;
	}

		// Level management	
	bool lmb = true;


	if (score == 5)
	{
		currentLevel++ ;
		sleepLevel--;
		score++; 
	}
	else if (score == 10)
	{
		currentLevel++;
		sleepLevel--;
		score++; 

	}
	else if (score == 15)
	{
		currentLevel++;
		sleepLevel--;
		score++; 

	}
	else if (score == 20)
	{
		currentLevel++;
		sleepLevel--;
		score++; 

	}
	else if (score == 25)
	{
		currentLevel++;
		sleepLevel--;
		score++; 

	}
	else if (score == 30)
	{
		currentLevel++;
		sleepLevel--;
		score++; 

	}


}


int main()
{
	char R;
	bool restart = true;

	while (restart) {

		Setup();
		Draw();
		while (!gameOver)
		{
			Draw();
			Input();
			Logic();
			Sleep(sleepLevel);//  I can use it later to control speed and levels
		}
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "          ***************************************" << endl;
		cout << "                  Your Final Score is " << score << endl;
		cout << "          ***************************************" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "Press 'X' to exit or 'A' to play again: ";
		R = 'H';
		while (R != 'A' && R != 'a' && R != 'X' && R != 'x')
			{R = _getch();}
				

		if (R == 'X' || R == 'x')
		{
		
			restart = false;
		}
		else if ((R == 'A' || R == 'a'))
		{
		
			restart = true;


		}

		
	}

	return 0;
}
