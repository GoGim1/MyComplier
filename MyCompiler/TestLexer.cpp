#include "UnitTest.h"

using namespace Complier;

TEST_CASE(testIdentifier)
{
	string code = "idone idtwo idthree  ";
	Parse(code);
	TEST_ASSERT(tokenStream.size() == 3);
}

TEST_CASE(wrongInput1)
{
	string code = "asd[ ";
	Parse(code);
	TEST_ASSERT(errorList.size() == 1);
	TEST_ASSERT(errorList[0]->errorPos.line == 1);
	TEST_ASSERT(errorList[0]->errorPos.index == 5);
}