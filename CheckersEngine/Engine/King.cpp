#include "King.h"
#include <iostream>
#include <algorithm>
#include"BoardUtilities.h"
using std::swap;
using std::vector;
void King::capture(Tree& t)
{
	short ratiox = -1, ratioy = -1, direction = 0;
	Tree temp;
	sboard::copy(temp.board_, t.board_);

	while (direction != 4) //move in four sides
	{
		changeDirection(direction, ratiox, ratioy);

		for (int z = 1; z < boardXY; z++)
		{
			if (z * ratioy + y_ < boardXY - 1 && z * ratioy + y_ > 0 && z * ratiox + x_ < boardXY - 1 && z * ratiox + x_ > 0)
			//borders
			{
				if (temp.board_[y_ + z * ratioy][x_ + z * ratiox] + player_ == 2 || temp.board_[y_ + z * ratioy][x_ + z * ratiox] + player_ == 5)
					break;
				if (temp.board_[y_ + z * ratioy][x_ + z * ratiox] + !player_ == 2 || temp.board_[y_ + z * ratioy][x_ + z * ratiox] + !player_ == 5) 
					//if opponent is is on the road
				{
					if (temp.board_[y_ + (z + 1) * ratioy][x_ + (z + 1) * ratiox] == 0) //if  there is a empty space behind an opponent
					{
						swap(temp.board_[y_ + (z + 1) * ratioy][x_ + (z + 1) * ratiox], temp.board_[y_][x_]);
						const char capturedMan = temp.board_[y_ + z * ratioy][x_ + z * ratiox];
						temp.board_[y_ + z * ratioy][x_ + z * ratiox] = 0;
						sboard::copy(t.board_, temp.board_);
						t.next_.push_back(temp);
						moveCapture(t, ratioy, ratiox, y_ + (z + 1) * ratioy, x_ + (z + 1) * ratiox);
						multiCapture(t, y_ + (z + 1) * ratioy, x_ + (z + 1) * ratiox);
						swap(temp.board_[y_ + (z + 1) * ratioy][x_ + (z + 1) * ratiox], temp.board_[y_][x_]);
						temp.board_[y_ + z * ratioy][x_ + z * ratiox] = capturedMan;
						sboard::copy(t.board_, temp.board_);
						break;
					}
					break;
				}
			}
		}
	}
}

void King::multiCapture(Tree& t, char y, char x)
{
	short ratiox = -1, ratioy = -1, direction = 0;
	Tree temp;
	bool different = true;
	sboard::copy(temp.board_, t.board_);

	while (direction != 4) //move in four sides
	{
		changeDirection(direction, ratiox, ratioy);

		for (int z = 1; z < boardXY; z++)
		{
			if (z * ratioy + y < boardXY - 1 && z * ratioy + y > 0 && z * ratiox + x < boardXY - 1 && z * ratiox + x > 0)
				//borders
			{
				if (temp.board_[y + z * ratioy][x + z * ratiox] + player_ == 2 || temp.board_[y + z * ratioy][x + z * ratiox] + player_ == 5)
					break;
				if (temp.board_[y + z * ratioy][x + z * ratiox] + !player_ == 2 || temp.board_[y + z * ratioy][x + z * ratiox] + !player_ == 5) 
					//if opponent is is on the road
				{
					if (temp.board_[y + (z + 1) * ratioy][x + (z + 1) * ratiox] == 0) //if  there is a empty space behind an opponent
					{
						swap(temp.board_[y + (z + 1) * ratioy][x + (z + 1) * ratiox], temp.board_[y][x]);
						const char capturedMan = temp.board_[y + z * ratioy][x + z * ratiox];
						temp.board_[y + z * ratioy][x + z * ratiox] = 0;
						sboard::copy(t.board_, temp.board_);

						for (auto& i : t.next_)	//protected against doubling data
							if (i==temp)
								different = false;

						if (different)
						{
							t.next_.push_back(temp); //adds to the tree
						}
						moveCapture(t, ratioy, ratiox, y + (z + 1) * ratioy, x + (z + 1) * ratiox);
						multiCapture(t, y + (z + 1) * ratioy, x + (z + 1) * ratiox);
						swap(temp.board_[y + (z + 1) * ratioy][x + (z + 1) * ratiox], temp.board_[y][x]);
						temp.board_[y + z * ratioy][x + z * ratiox] = capturedMan;
						sboard::copy(t.board_, temp.board_);
						break;
					}
					else break;
				}
			}
		}
	}
}

void King::moveCapture(Tree& t, short ratioy, short ratiox, char y, char x)
{
	Tree temp;
	vector<Tree> result;
	sboard::copy(temp.board_, t.board_);
	bool different = true;

	for (int z = 1; z < boardXY; z++) //moves a few field in one move
	{
		if (z * ratioy + y < boardXY && z * ratioy + y >= 0 && z * ratiox + x < boardXY && z * ratiox + x >= 0) //borders
		{
			if (temp.board_[y + z * ratioy][x + z * ratiox] == 0)
			{
				swap(temp.board_[y + z * ratioy][x + z * ratiox], temp.board_[y][x]);

				for (auto& i : t.next_)
					if (i==temp)
						different = false;

				if (different) //protects against doubling data
				{
					t.next_.push_back(temp); //adds to the tree
				}

				sboard::copy(t.board_, temp.board_);
				multiCapture(t, y + z * ratioy, x + z * ratiox);
				swap(temp.board_[y + z * ratioy][x + z * ratiox], temp.board_[y][x]);
				sboard::copy(t.board_, temp.board_);
			}
			else break;
		}
	}
}

void King::move(Tree& t)
{
	Tree temp;
	short ratiox = -1, ratioy = -1, direction = 0;
	sboard::copy(temp.board_, t.board_);

	while (direction != 4) //move in four sides
	{
		changeDirection(direction, ratiox, ratioy);


		for (int z = 1; z < boardXY; z++) //moves a few field in one move
		{
			if (z * ratioy + y_ < boardXY && z * ratioy + y_ >= 0 && z * ratiox + x_ < boardXY && z * ratiox + x_ >= 0)
				//borders
			{
				if (temp.board_[y_ + z * ratioy][x_ + z * ratiox] == 0)
				{
					swap(temp.board_[y_ + z * ratioy][x_ + z * ratiox], temp.board_[y_][x_]);
					t.next_.push_back(temp);
					swap(temp.board_[y_ + z * ratioy][x_ + z * ratiox], temp.board_[y_][x_]);
				}
				else break;
			}
		}
	}
}
