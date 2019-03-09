#include "Tests.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include<array>
#include<chrono>
#include "../Engine/BoardUtilities.h"
using std::cout;
using std::endl;
using arrayboard = std::array<std::array<char, 8>, 8>;
void gotoxy(int x, int y)	//goes to the (X,Y) coordinates
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Tests::printTest(std::string testName, std::array<std::array<char, boardXY>, boardXY> arrayb, int id)
{

	changearrayboard(arrayb);	//change board
	generateMove(tree_, 1);	//generate all possible moves
	readTestName(testName);
	sboard::print(tree_.board_);
	getchar();
	gotoxy(0, 0);

	Tree temp;
	int moves = 0;
	for (auto i : tree_.next_)	//count moves
	{
		readTestName(testName);
		moves++;
		sboard::print(i.board_);
		getchar();
		gotoxy(0, 0);
	}
	if (!uniquesscheck(tree_.next_))
	{
		gotoxy(5, boardXY + 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "REPETITIVE MOVES\n";
		getchar();
		getchar();
	}
	readResult(moves, testResults[id]);
	system("cls");
}

bool Tests::uniquesscheck(std::vector<Tree> &moves)
{
	for (int i = 0; i<moves.size(); i++)
	{
		for (int j = i + 1; j < moves.size(); j++)
		{
			if (i == j)
			{
				return false;
			}
		}

	}
	return true;
}

void Tests::changearrayboard(std::array<std::array<char, boardXY>, boardXY> arrayb)
{
	board b;
	for (int i = 0; i < boardXY; i++)
	{
		for (int j = 0; j < boardXY; j++)
		{
			b[i][j] = arrayb[i][j];
		}
	}
	changeBoard(b);
}

void Tests::test(int id)
{

	try
	{
		arrayboard b;
		switch (id)
		{
		case 0:
			b =
			{
				0,1,0,1,0,1,0,1,	//1 - black
				1,0,1,0,1,0,1,0,	//2 - white
				0,1,0,1,0,1,0,1,	//4 - black king
				0,0,0,0,0,0,0,0,	//5 - white king
				0,0,0,0,0,0,0,0,
				2,0,2,0,2,0,2,0,
				0,2,0,2,0,2,0,2,
				2,0,2,0,2,0,2,0, };
			printTest("Man moves",b, id);

			break;

		case 1:
			b = 
			{
				0,0,0,0,0,0,0,0,	//1 - black
				0,0,0,0,0,0,0,0,	//2 - white
				0,0,2,0,2,0,2,0,	//4 - black king
				0,0,0,1,0,0,0,0,	//5 - white king
				0,0,2,0,2,0,2,0,
				0,0,0,0,0,0,0,0,
				0,0,2,0,2,0,2,0,
				0,0,0,0,0,0,0,0, };

			printTest("Multiple capture",b, id);
			break;

		case 2:
			b = 
			{
				0,0,0,0,0,0,0,0,	//1 - black
				0,0,0,0,0,0,0,0,	//2 - white
				0,0,0,0,0,0,0,0,	//4 - black king
				0,0,0,0,4,0,0,0,	//5 - white king
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0, };

			printTest("King moves",b, id);
			break;

		case 3:
			b = 
			{
				0,0,0,0,0,0,0,0,	//1 - black
				0,2,0,2,0,2,0,0,	//2 - white
				0,0,1,0,0,0,0,0,	//4 - black king
				0,0,0,0,0,0,0,0,	//5 - white king
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,1,0,0,
				0,0,2,0,2,0,2,0,
				0,0,0,0,0,0,0,0, };

			printTest("Independence moves test",b, id);
			break;

		case 4:
			b = 
			{
				0,0,0,0,0,0,0,0,	//1 - black
				0,0,0,0,0,0,0,0,	//2 - white
				0,0,0,0,0,2,0,0,	//4 - black king
				0,0,0,0,4,0,0,0,	//5 - white king
				0,0,0,0,0,0,0,0,
				0,0,2,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0, };

			printTest("King capturing",b, id);
			break;

		case 5:
			b = 
			{
				0,0,0,0,0,0,0,0,	//1 - black
				0,0,0,0,0,0,2,0,	//2 - white
				0,0,0,0,0,0,0,0,	//4 - black king
				0,0,0,0,2,0,0,0,	//5 - white king
				0,0,0,0,0,0,0,0,
				0,0,4,0,0,0,0,0,
				0,0,0,0,0,4,0,0,
				0,0,0,0,0,0,0,0, };

			printTest("Multiple king capturing",b, id);
			break;

		case 6:
			b = 
			{
				0,0,0,0,0,0,0,0,	//1 - black
				0,0,0,0,0,0,0,0,	//2 - white
				0,0,0,0,0,0,0,0,	//4 - black king
				0,0,0,0,0,0,0,0,	//5 - white king
				0,0,0,2,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,2,0,0,0,0,0,0,
				4,0,0,0,0,0,4,0, };

			printTest("Independence moves test",b, id);
			break;

		case 7:
			b = 
			{
				0,0,0,0,0,0,0,0,	//1 - black
				0,0,0,0,0,0,0,0,	//2 - white
				0,0,2,0,2,0,2,0,	//4 - black king
				0,0,0,4,0,0,0,0,	//5 - white king
				0,0,2,0,2,0,2,0,
				0,0,0,0,0,0,0,0,
				0,0,2,0,2,0,2,0,
				0,0,0,0,0,0,0,0, };

			printTest("Multiple king capturing",b, id);
			break;

		case 8:
			b = 
			{
				0,0,0,0,0,0,0,0,	//1 - black
				0,0,0,0,0,0,0,0,	//2 - white
				0,0,0,0,0,0,0,0,	//4 - black king
				0,0,0,0,0,0,0,0,	//5 - white king
				0,2,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,2,0,4,0,0,0,0,
				4,0,0,0,0,0,0,0, };

			printTest("Independence moves test",b, id);
			break;

		case 9:
			b = 
			{
				0,0,0,0,0,0,0,0,	//1 - black
				0,0,0,0,0,0,0,0,	//2 - white
				0,0,2,0,2,0,2,0,	//4 - black king
				0,0,0,4,0,0,0,0,	//5 - white king
				0,0,2,0,2,0,2,0,
				0,0,0,0,0,0,0,0,
				0,0,2,0,2,0,2,0,
				0,0,0,0,0,0,0,0, };
			changearrayboard(b);
			sboard::print(tree_.board_);
			readTestName("Choosing the best move");
			getBestMove(1, 8); // depth
			sboard::print(tree_.board_);
			readTestName("Choosing the best move");
			getchar();
			break;

		case 10:	//not implemented yet
			b = 
			{
				0,1,0,1,0,1,0,1,	//1 - black
				1,0,1,0,1,0,1,0,	//2 - white
				0,1,0,1,0,1,0,1,	//4 - black king
				0,0,0,0,0,0,0,0,	//5 - white king
				0,0,0,0,0,0,0,0,
				2,0,2,0,2,0,2,0,
				0,2,0,2,0,2,0,2,
				2,0,2,0,2,0,2,0, };
			//sboard::print(b);
			readTestName("Test Game");
			break;

		default:
			break;
		}
		gotoxy(0, boardXY + 2);

	}
	catch(std::exception exc)
	{
		cout << exc.what() << endl;
		return;
	}
}

	void Tests::readTestName(std::string name)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		gotoxy(boardXY * 2, 0);
		cout << name << endl;
	}

	void Tests::readResult(int testResult, int test)
	{
		gotoxy(boardXY*2, 2);
		if (testResult == test)
		{

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "Correct " << testResult << "/" << test;
		}
		else
		{
			gotoxy(boardXY * 2, 2);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Incorrect " << testResult << "/" << test;

		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		getchar();
	}
	void Tests::alltests()
	{
		for (int i = 0; i < Testsnumber; i++)
		{
			test(i);
		}
	}

	double Tests::performanceTest()
	{
		AI ai;
		bool player = true;
		int depth = 10;
		sboard::print(ai.tree_.board_);
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < 10; i++)	//just few first moves
		{
			ai.getBestMove(player, depth);
			sboard::print(ai.tree_.board_);
			player = !player;
		}
		auto end = std::chrono::system_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		return elapsed_time.count();	//elapsing time
	}

