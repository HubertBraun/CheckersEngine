#include "AI.h"
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include<stack>
#include"BoardUtilities.h"
using std::make_unique;
AI::AI()
{
	board b
	{
		0, 1, 0, 1, 0, 1, 0, 1, //1 - black
		1, 0, 1, 0, 1, 0, 1, 0, //2 - white
		0, 1, 0, 1, 0, 1, 0, 1, //4 - black king
		0, 0, 0, 0, 0, 0, 0, 0, //5 - white king
		0, 0, 0, 0, 0, 0, 0, 0,
		2, 0, 2, 0, 2, 0, 2, 0,
		0, 2, 0, 2, 0, 2, 0, 2,
		2, 0, 2, 0, 2, 0, 2, 0,
	};

	changeBoard(b);
}


void AI::changeBoard(board b)
{
	pieces_.clear();
	tree_.next_.clear();
	sboard::copy(tree_.board_, b);

	for (int y = 0; y < boardXY; y++)
	{
		for (int x = 0; x < boardXY; x++)
		{
			switch (tree_.board_[y][x])
			{
			case 1:
				pieces_.push_back(make_unique<Man>(x, y, 1)); //black
				break;
			case 2:
				pieces_.push_back(make_unique<Man>(x, y, 0)); //white
				break;
			case 4:
				pieces_.push_back(make_unique<King>(x, y, 1)); //black
				break;
			case 5:
				pieces_.push_back(make_unique<King>(x, y, 0)); //white
				break;
			default:
				break;
			}
		}
	}
}

void AI::generateMove(Tree& t, bool player)
{
	pieces_.clear();
	for (int y = 0; y < boardXY; y++)
	{
		for (int x = 0; x < boardXY; x++)
		{
			switch (t.board_[y][x])
			{
			case 1:
				pieces_.push_back(make_unique<Man>(x, y, 1)); //black
				break;
			case 2:
				pieces_.push_back(make_unique<Man>(x, y, 0)); //white
				break;
			case 4:
				pieces_.push_back(make_unique<King>(x, y, 1)); //black
				break;
			case 5:
				pieces_.push_back(make_unique<King>(x, y, 0)); //white
				break;
			default:
				break;
			}
		}
	}
	if (pieces_.empty())
		return;

	for (auto& f : pieces_)	//first capturing
	{
		if (f->player_ == player)
		{
			f->capture(t);
		}
	}

	if (t.next_.empty())	//next moving
	{
		for (auto& f : pieces_)
		{
			if (f->player_ == player)
			{
				f->move(t);
			}
		}
	}
	pieceToKing(t);
}


void AI::pieceToKing(Tree& t)
{
	for (auto& i : t.next_)
	{
		for (int x = 0; x < boardXY; x++)
		{
			if (i.board_[0][x] == 2)	//white
			{
				i.board_[0][x] = 5;
			}
			if (i.board_[7][x] == 1)	//black
			{
				i.board_[7][x] = 4;
			}
		}
	}
}

int evaluate(const Tree& t, bool player)
{
	board b		
	{
		4, 4, 4, 4, 4, 4, 4, 4, //evaluate board
		4, 0, 3, 3, 3, 3, 3, 4, 
		4, 3, 2, 2, 2, 2, 3, 4, 
		4, 3, 2, 1, 1, 2, 3, 4, 
		4, 3, 2, 1, 1, 2, 3, 4,
		4, 3, 2, 2, 2, 2, 3, 4,
		4, 3, 3, 3, 3, 3, 3, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
	};


	int toReturn = 0;	//rating of this board
	int pieces = 0, piecesOP = 0;	//number of player and opponent pieces
	for (int y = 0; y < boardXY; y++)
	{
		for (int x = 0; x < boardXY; x++)
		{
			if (t.board_[y][x] + player == 2)
			{
				toReturn += b[y][x];
				pieces++;
			}
			else if (t.board_[y][x] + !player == 2)
			{
				toReturn -= b[y][x];
				piecesOP++;
			}
			else if (t.board_[y][x] + player == 5)
			{
				toReturn += b[y][x] * 2;
				pieces++;
			}
			else if (t.board_[y][x] + !player == 5)
			{
				toReturn -= b[y][x] * 2;
				piecesOP++;
			}
		}
	}
	if (piecesOP == 0)
		return 100;
	if (pieces == 0)
		return -100;
	return toReturn;
}

void AI::getBestMove(bool player, int depth)
{
	int best = -1000000;
	int result;
	board bestBoard;
	generateMove(tree_, player);
	for (auto& k : tree_.next_)
	{
		if (player)
			result = -negamax(k, depth, -1, -1000, 1000);
		else
			result = -negamax(k, depth, 1, -1000, 1000);

		if (result > best)
		{
			best = result;
			sboard::copy(bestBoard, k.board_);
		}
		k.next_.clear();
	}

	changeBoard(bestBoard);
}

int AI::negamax(Tree &t, int depth, int colour, int alpha, int beta)
{
	if (depth != 0) //there is no need to search the last level of the tree
	{
		if (colour == 1)
			generateMove(t, true);
		else
			generateMove(t, false);
	}
	if (depth == 0 || t.next_.empty())
		return colour * evaluate(t, 1) - depth; //faster win is better
	std::sort(t.next_.begin(), t.next_.end(), [](Tree& t1, Tree& t2)
	{
		return evaluate(t1, 1) < evaluate(t2, 1);
	});

	for (auto& i : t.next_)
	{
		int temp = -negamax(i, depth - 1, -colour, -beta, -alpha);
		alpha = max(alpha, temp);

		if (alpha >= beta)
			break;
	}
	return alpha;
}
bool AI::win(bool player)
{
	generateMove(tree_, player);
	if (tree_.next_.empty())
	{
		return true;
	}
	return false;
}