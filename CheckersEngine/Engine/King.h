#pragma once
#include "Tree.h"
#include <vector>
#include "Piece.h"

class King : public Piece
{
	void moveCapture(Tree& t, short ratioy, short ratiox, char y, char x);	//move after capture
	void multiCapture(Tree& t, char y, char x);	//check if king can capture more pieces
public:
	King(char x, char y, bool player) : Piece(x, y, player){}
	void move(Tree& t) override;
	void capture(Tree& t) override;
	~King() = default;
};
