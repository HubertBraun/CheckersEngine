#pragma once
#include <vector>
#include "../pch.h"
struct Tree		//movement tree
{
	board board_ = {
			0, 1, 0, 1, 0, 1, 0, 1, //1 - black	
			1, 0, 1, 0, 1, 0, 1, 0, //2 - white
			0, 1, 0, 1, 0, 1, 0, 1, //4 - black king
			0, 0, 0, 0, 0, 0, 0, 0, //5 - white king
			0, 0, 0, 0, 0, 0, 0, 0,
			2, 0, 2, 0, 2, 0, 2, 0,
			0, 2, 0, 2, 0, 2, 0, 2,
			2, 0, 2, 0, 2, 0, 2, 0,
	};
	std::vector<Tree> next_;
	Tree() = default;
	bool operator<(const Tree& t)
	{
		for (int y = 0; y < boardXY; y++)
		{
			for (int x = 0; x < boardXY; x++)
			{
				if (this->board_[y][x] < t.board_[y][x])
					return false;
			}
		}
		return true;
	}

	bool operator>(const Tree& t)
	{
		for (int y = 0; y < boardXY; y++)
		{
			for (int x = 0; x < boardXY; x++)
			{
				if (this->board_[y][x] > t.board_[y][x])
					return false;
			}
		}
		return true;
	}

	bool operator==(const Tree& t)
	{
		for (int y = 0; y < boardXY; y++)
		{
			for (int x = 0; x < boardXY; x++)
			{
				if (this->board_[y][x] != t.board_[y][x])
					return false;
			}
		}
		return true;
	}
};
