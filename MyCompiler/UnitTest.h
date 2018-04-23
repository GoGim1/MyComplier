#pragma once
#include <iostream>
#include "Lexer.h"

using namespace std;

#define TEST_CASE(NAME)								\
	extern void TEST_CASE_FUNCTION_##NAME();		\
	class TEST_CASE_CLASS_##NAME					\
	{												\
	public:											\
		TEST_CASE_CLASS_##NAME()					\
		{											\
			std::cout << #NAME << std::endl;		\
			TEST_CASE_FUNCTION_##NAME();			\
		}											\
	} TEST_CASE_INSTANCE_##NAME;					\
	void TEST_CASE_FUNCTION_##NAME()		

#define TEST_ASSERT(CONDITION) do {	if (!(CONDITION)) throw 0;} while(0)


