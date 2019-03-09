#pragma once
#include <string>
#include"../Engine/AI.h"
#define Testsnumber 11
class Tests : AI
{
private:
	int testResults[Testsnumber]{ 7, 31, 13, 6, 8, 2, 8, 210, 8, 1, 121};	//possible combination moves

	inline void readTestName(std::string name);
	void readResult(int testResult, int test);
	void printTest(std::string testName,std::array<std::array<char, boardXY>, boardXY> arrayb, int id);
	bool uniquesscheck(std::vector<Tree> &moves);
	void changearrayboard(std::array<std::array<char, boardXY>, boardXY> arrayb);
public:
	void test(int id);
	void alltests();
	double performanceTest();
};
