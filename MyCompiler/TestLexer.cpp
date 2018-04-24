#include "UnitTest.h"

using namespace Complier;

TEST_CASE(testIdentifier)
{
	{
		string code = R"wu(idone idtwo idthree  
)wu";
		Token::Vec tokenStream;
		Error::Vec errorList;
		Parse(code, tokenStream, errorList);
		TEST_ASSERT(tokenStream.size() == 3);
		TEST_ASSERT(tokenStream[0]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[0]->tokenPos.index == 0);
		TEST_ASSERT(tokenStream[1]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[1]->tokenPos.index == 6);
		TEST_ASSERT(tokenStream[2]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[2]->tokenPos.index == 12);
	}
	{
		string code = R"wu(a b
c
	d)wu";
		Token::Vec tokenStream;
		Error::Vec errorList;
		Parse(code, tokenStream, errorList);
		TEST_ASSERT(tokenStream.size() == 4);
		TEST_ASSERT(tokenStream[0]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[0]->tokenPos.index == 0);
		TEST_ASSERT(tokenStream[1]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[1]->tokenPos.index == 2);
		TEST_ASSERT(tokenStream[2]->tokenPos.line == 1);
		TEST_ASSERT(tokenStream[2]->tokenPos.index == 0);
		TEST_ASSERT(tokenStream[3]->tokenPos.line == 2);
		TEST_ASSERT(tokenStream[3]->tokenPos.index == 1);
	}
	{
		string code = R"wu(	idone 
idtwo 

	idthree)wu";
		Token::Vec tokenStream;
		Error::Vec errorList;
		Parse(code, tokenStream, errorList);
		TEST_ASSERT(tokenStream.size() == 3);
		TEST_ASSERT(tokenStream[0]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[0]->tokenPos.index == 1);
		TEST_ASSERT(tokenStream[1]->tokenPos.line == 1);
		TEST_ASSERT(tokenStream[1]->tokenPos.index == 0);
		TEST_ASSERT(tokenStream[2]->tokenPos.line == 3);
		TEST_ASSERT(tokenStream[2]->tokenPos.index == 1);
	}
}

TEST_CASE(testWrongInput)
{
	{
		string code = R"wu(a[bc asg
s]
[[]	a
])wu";
		Token::Vec tokenStream;
		Error::Vec errorList;
		Parse(code, tokenStream, errorList);
		TEST_ASSERT(tokenStream.size() == 4);
		TEST_ASSERT(tokenStream[0]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[0]->tokenPos.index == 0);
		TEST_ASSERT(errorList.size() == 4);
		TEST_ASSERT(errorList[0]->errorPos.line == 0);
		TEST_ASSERT(errorList[0]->errorPos.index == 1);
		TEST_ASSERT(errorList[1]->errorPos.line == 1);
		TEST_ASSERT(errorList[1]->errorPos.index == 1);
		TEST_ASSERT(errorList[2]->errorPos.line == 2);
		TEST_ASSERT(errorList[2]->errorPos.index == 0);
		TEST_ASSERT(errorList[3]->errorPos.line == 3);
		TEST_ASSERT(errorList[3]->errorPos.index == 0);
	}

}

TEST_CASE(testComment)
{
	{
		string code = R"wu(#a
#a bc
ab#a)wu";
		Token::Vec tokenStream;
		Error::Vec errorList;
		Parse(code, tokenStream, errorList);
		TEST_ASSERT(tokenStream.size() == 4);
		TEST_ASSERT(tokenStream[0]->tokenPos.line == 0);
		TEST_ASSERT(tokenStream[0]->tokenPos.index == 0);
		TEST_ASSERT(tokenStream[1]->tokenPos.line == 1);
		TEST_ASSERT(tokenStream[1]->tokenPos.index == 0);
		TEST_ASSERT(tokenStream[2]->tokenPos.line == 2);
		TEST_ASSERT(tokenStream[2]->tokenPos.index == 0);
		TEST_ASSERT(tokenStream[3]->tokenPos.line == 2);
		TEST_ASSERT(tokenStream[3]->tokenPos.index == 2);
	}
}

TEST_CASE(testNumber)
{
	{
		string code = R"wu(12 35
	54.2 1.
3.)wu";
		Token::Vec tokenStream;
		Error::Vec errorList;
		Parse(code, tokenStream, errorList);
		TEST_ASSERT(tokenStream.size() == 5);
	}
}


