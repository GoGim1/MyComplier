#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LexerTest
{		
	using namespace Lexer;
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestErrorInput)
		{
			string code = "ina] ";
			Parse()
		}
		TEST_METHOD(TestErrorInput2)
		{
			string code = "ina]a  aasf";

		}
		TEST_METHOD(TestErrorInput3)
		{
			string code = "ina]aasdf asfd][a ";

		}
		TEST_METHOD(TestErrorInput4)
		{
			string code = "ina]";

		}
	};
}