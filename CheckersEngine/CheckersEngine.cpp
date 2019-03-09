//Checkers Engine using minmax alghoritm with alpha-beta cutoff
//
//
#include <iostream>
#include"Engine/Tree.h"
#include"Engine/AI.h"
#include"Engine/BoardUtilities.h"
#include"Tests/Tests.h"
#include<chrono>
#define debug 0	// 0 - release, 1 -debug

int main()
{
#ifdef debug
	#if debug == 0
		AI ai;
		bool player = true;
		sboard::print(ai.tree_.board_);
		while (!ai.win(player))	//test of the alghoritm
		{
			ai.getBestMove(player, 8);	// 8 - depth
			getchar();
			sboard::print(ai.tree_.board_);
			player = !player;
		}
		std::cout << "Winner: " << ((player) ? ("red") : ("blue")) << std::endl;
	#else
	Tests t;
	std::cout << "Elapsed time: " << t.performanceTest() / 1000.0 << "s" << std::endl;
	#endif
#endif
	return 0;
}