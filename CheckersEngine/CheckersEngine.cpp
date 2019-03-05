//Checkers Engine using minmax alghoritm with alpha-beta cutoff
//
//
#include <iostream>
#include"Engine/Tree.h"
#include"Engine/AI.h"
#include"Engine/BoardUtilities.h"
#include"Tests/Tests.h"
#define debug 0	// 0 - release, 1 -debug

int main()
{
#ifdef debug
	#if debug == 0
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
	#else
	Tests t;
	t.test(10);
	#endif
#endif
	return 0;
}