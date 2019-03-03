//Checkers Engine using minmax alghoritm with alpha-beta cutoff
//
//
#include <iostream>
#include"Engine/Tree.h"
#include"Engine/AI.h"
#include"Engine/BoardUtilities.h"
int main()
{
	AI ai;
	Tree t;
	bool player = true;

	sboard::print(t.board_);
	ai.getBestMove(t, player, 7);
	getchar();
	sboard::print(ai.tree_.board_);
	player = false;
	while (1)	//test of the alghoritm
	{
		ai.getBestMove(ai.tree_, player, 7);
		getchar();
		sboard::print(ai.tree_.board_);
		player = !player;
	}
	return 0;
}