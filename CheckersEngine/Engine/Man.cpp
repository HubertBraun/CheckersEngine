#include "Man.h"
#include <iostream>
#include"BoardUtilities.h"
using namespace std;

void Man::capture(Tree& t)
{
	short ratiox = -1, ratioy = -1, direction = 0;
	Tree temp;
	char p[8][8];
	sboard::copy(temp.board_, t.board_);
	sboard::copy(p, t.board_);

	while (direction != 4) //capture in four sides
	{
		changeDirection(direction, ratiox, ratioy);
		
		if (ratiox < 0 && ratioy > 0 && y_ < boardXY - 2 && x_ > 1 || ratiox > 0 && ratioy > 0 && y_ < boardXY - 2 && x_ <
			boardXY - 2 || ratiox < 0 && ratioy < 0 && y_ > 1 && x_ > 1 || ratiox > 0 && ratioy < 0 && y_ > 1 && x_ < boardXY - 2) 
			//borders
		{
			if (temp.board_[ratioy + y_][ratiox + x_] + !player_ == 2 && temp.board_[ratioy * 2 + y_][ratiox * 2 + x_] == 0 ||
				temp.board_[ratioy + y_][ratiox + x_] + !player_ == 5 && temp.board_[ratioy * 2 + y_][ratiox * 2 + x_] == 0) //if capture is possible
			{
				swap(temp.board_[ratioy * 2 + y_][ratiox * 2 + x_], temp.board_[y_][x_]);
				const char capturedMan = temp.board_[ratioy + y_][ratiox + x_];
				temp.board_[ratioy + y_][ratiox + x_] = 0;
				//adds to the tree
				t.next_.push_back(temp);
				sboard::copy(t.board_, temp.board_);
				multiCapture(t, ratioy * 2 + y_, ratiox * 2 + x_); //checks if man can capture few pieces
				sboard::copy(t.board_, p);

				swap(temp.board_[ratioy * 2 + y_][ratiox * 2 + x_], temp.board_[y_][x_]);
				temp.board_[ratioy + y_][ratiox + x_] = capturedMan;
			}
		}
	}
}

void Man::multiCapture(Tree& t, char y, char x)
{
	short ratiox = -1, ratioy = -1, direction = 0;
	Tree temp;
	sboard::copy(temp.board_, t.board_);


	while (direction != 4) //capture in four sides
	{
		changeDirection(direction, ratiox, ratioy);

		if (ratiox < 0 && ratioy > 0 && y < boardXY - 2 && x > 1 || ratiox > 0 && ratioy > 0 && y < boardXY - 2 && x < boardXY -
			2 || ratiox < 0 && ratioy < 0 && y > 1 && x > 1 || ratiox > 0 && ratioy < 0 && y > 1 && x < boardXY - 2)
			//borders
		{
			if (temp.board_[ratioy + y][ratiox + x] + !player_ == 2 && temp.board_[ratioy * 2 + y][ratiox * 2 + x] == 0 ||
				temp.board_[ratioy + y][ratiox + x] + !player_ == 5 && temp.board_[ratioy * 2 + y][ratiox * 2 + x] == 0) //if capture is possible
			{
				swap(temp.board_[ratioy * 2 + y][ratiox * 2 + x], temp.board_[y][x]);
				const char capturedMan = temp.board_[ratioy + y][ratiox + x];
				temp.board_[ratioy + y][ratiox + x] = 0;

				bool different = true;
				for (auto& i : t.next_)
					if (i==temp)
						different = false;

				if (different) //protects against doubling data
				{
					t.next_.push_back(temp); //adds to the tree
					sboard::copy(t.board_, temp.board_);
					multiCapture(t, ratioy * 2 + y, ratiox * 2 + x); //recursion
				}
				swap(temp.board_[ratioy * 2 + y][ratiox * 2 + x], temp.board_[y][x]);
				temp.board_[ratioy + y][ratiox + x] = capturedMan;
			}
		}
	}
}

void Man::move(Tree& t)
{
	short ratioy = -1, ratiox = -1;
	if (player_)
		ratioy = 1; //black move

	Tree temp;
	sboard::copy(temp.board_, t.board_);
	while (ratiox != 0)
	{
		if (ratiox < 0 && ratioy > 0 && y_ < boardXY - 1 && x_ > 0 || ratiox > 0 && ratioy > 0 && y_ < boardXY - 1 && x_ < boardXY - 1 ||
			ratiox < 0 && ratioy < 0 && y_ > 0 && x_ > 0 || ratiox > 0 && ratioy < 0 && y_ > 0 && x_ < boardXY - 1)
			//if move is possible
		{
			if (temp.board_[ratioy + y_][ratiox + x_] == 0)
			{
				swap(temp.board_[y_][x_], temp.board_[ratioy + y_][ratiox + x_]);
				t.next_.push_back(temp);
				swap(temp.board_[y_][x_], temp.board_[ratioy + y_][ratiox + x_]);
			}
		}

		if (ratiox == 1) //changes direction
			ratiox = 0;
		else
			ratiox = 1;
	}
}


