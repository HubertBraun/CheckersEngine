#pragma once
#include <utility>
#include"Tree.h"
class Piece
{
protected:
	void changeDirection(short& direction, short& ratiox, short& ratioy); //changes direction of capturing
public:
	virtual void move(Tree& t) = 0;
	virtual void capture(Tree& t) = 0;
	char x_, y_;
	bool player_;
	Piece(char x, char y, bool player) : x_(x), y_(y), player_(player){}
	~Piece() = default;
};
