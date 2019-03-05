#pragma once
#include"../pch.h"

namespace sboard {
	void clean();	//cleans the board
	void copy(board out, board in);	//copies the board
	void print(board b);	//displays the board
	bool compare(board b1, board b2);
};