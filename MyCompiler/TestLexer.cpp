#include "UnitTest.h"

using namespace Complier;

TEST_CASE(testIdentifier)
{
	{
		string code = "idone idtwo idthree  ";
		Token::Vec tokenStream;
		Parse(code, tokenStream);
		TEST_ASSERT(tokenStream.size() == 3);
		TEST_ASSERT(tokenStream[0]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[0]->tokenPos.index == 0);
		TEST_ASSERT(tokenStream[1]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[1]->tokenPos.index == 6);
		TEST_ASSERT(tokenStream[2]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[2]->tokenPos.index == 12);
	}
	{
		string code = R"wu(	idone 
idtwo 

	idthree)wu";
		Token::Vec tokenStream;
		Parse(code, tokenStream);
		TEST_ASSERT(tokenStream.size() == 3);
		TEST_ASSERT(tokenStream[0]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[0]->tokenPos.index == 1);
		TEST_ASSERT(tokenStream[1]->tokenPos.line == 1);
		TEST_ASSERT(tokenStream[1]->tokenPos.index == 0);
		TEST_ASSERT(tokenStream[2]->tokenPos.line == 3);
		TEST_ASSERT(tokenStream[2]->tokenPos.index == 1);
	}
}



//TEST_CASE(wrongInput)
//{
//	
//	{
//		string code = "asd[ ";
//		Parse(code);
//		TEST_ASSERT(errorList.size() == 1);
//		TEST_ASSERT(errorList[0]->errorPos.line == 0);
//		TEST_ASSERT(errorList[0]->errorPos.index == 3);
//	}
//	{
//		string code = "asd[";
//		Parse(code);
//		TEST_ASSERT(errorList.size() == 1);
//		TEST_ASSERT(errorList[0]->errorPos.line == 0);
//		TEST_ASSERT(errorList[0]->errorPos.index == 3);
//	}
//	{
//		string code = R"wu(asd[
//			)wu";
//		Parse(code);
//		TEST_ASSERT(errorList.size() == 1);
//		TEST_ASSERT(errorList[0]->errorPos.line == 0);
//		TEST_ASSERT(errorList[0]->errorPos.index == 3);
//	}
//}


