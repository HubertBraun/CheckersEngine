#pragma once
#include "Tree.h"
#include "Piece.h"

class Man : public Piece
{
	void multiCapture(Tree& t, char y, char x);
public:
	Man(char x, char y, bool player) : Piece(x, y, player){}
	void move(Tree& t) override;
	void capture(Tree& t) override;
	~Man() = default;
};
