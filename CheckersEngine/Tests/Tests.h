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
	void printTest(std::string testName,std::array<std::array<char,8>,8> arrayb, int id);
	bool uniquesscheck(std::vector<Tree> &moves);
public:
	void test(int id);
	void alltests();
};
