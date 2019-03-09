#include"BoardUtilities.h"
#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;

namespace sboard
{
	void gotoxy(int x, int y)	//goes to the (X,Y) coordinates
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	void copy(board out, board in)	//copies the board
	{
		for (int i = 0; i < boardXY; i++)
			for (int j = 0; j < boardXY; j++)
				out[i][j] = in[i][j];
	}

	void clean()	//cleanes the board
	{
		gotoxy(0, 0);
		for (int i = 0; i < boardXY; i++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
			for (int j = 0; j < boardXY / 2; j++)
			{

				if (i % 2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);	//dark grey
					cout << "  ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);	//light grey
					cout << "  ";
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
					cout << "  ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
					cout << "  ";
				}

			}
			cout << endl;
		}
	}

	void print(board b)	//displays the board
	{
		clean();	//cleans the screen
		for (int i = 0; i < boardXY; i++)
		{
			for (int j = 0; j < boardXY; j++)
			{
				gotoxy(j*2, i);	//only white fields
				switch (b[i][j])
				{
				case 1:	//black(on the top of the board)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
					cout << "  ";
					break;
				case 2:	//white 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
					cout << "  ";
					break;
				case 4:	 //black king
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_INTENSITY);
					cout << "  ";
					break;
				case 5: //white king
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_INTENSITY);
					cout << "  ";
					break;
				}
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);	//returns to the standard colour
		gotoxy(0, boardXY+2);
	}

	bool compare(board b1, board b2)
	{
		for (int y = 0; y < boardXY; y++)
		{
			for (int x = 0; x < boardXY; x++)
			{
				if (b1[y][x] != b2[y][x])
					return false;
			}
		}
		return true;
	}
}
