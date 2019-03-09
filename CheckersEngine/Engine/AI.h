#pragma once
#include "Tree.h"
#include <vector>
#include "Man.h"
#include "King.h"
#include <memory>
#include"../pch.h"
class AI
{

protected:
	void changeBoard(board b);	//updates the board
	std::vector<std::unique_ptr<Piece>> pieces_;	//vector of pieces
	friend int evaluate(const Tree& t, bool player);
	void pieceToKing(Tree &t);
	void generateMove(Tree &t, bool player);
public:
	Tree tree_;
	AI();
	~AI(){pieces_.clear();}	
	void getBestMove(bool player, int depth);
	int negamax(Tree &t, int depth, int colour, int alpha, int beta);
	bool win(bool player);
};
