#include "Lexer.h"

namespace Complier
{
	Error::Error(int errLine, int errIndex, string& errMsg)
	{
		errorMsg = errMsg;
		errorPos.line = errLine;
		errorPos.index = errIndex;
	}

	Error::Error()
	{
	}

	Error::~Error()
	{
	}

	Token::Token(int line, int index, TokenType type, string& val)
	{
		tokenPos.line = line;
		tokenPos.index = index;
		this->type = type;
		value = val;
	}

	Token::Token() 
	{
	}

	Token::~Token()
	{
	}

	Token::Vec							tokenStream;
	Error::Vec							errorList;

	void Parse(string &code)
	{
		enum class StateType
		{
			Start,
			End,
			Error,
			InInt,
			InFloat,
			InComment,
			InString,
			InIdentifier,
			InOperator
		};

		auto curr = code.begin(), end = code.end();
		string::iterator tokenBegin;
		StateType state = StateType::Start;
		int line = 1, index = 0;

		while (curr != end)
		{
			if (*curr == '\n') line++;
			index++;

			switch (state)
			{
			case StateType::Start:
				state =
					isdigit(*curr) ? StateType::InInt :
					isalpha(*curr) ? StateType::InIdentifier : (
					*curr == '+' || 
					*curr == '-' || 
					*curr == '*' || 
					*curr == '/' || 
					*curr == '(' || 
					*curr == ')' ||
					*curr == ',' ||
					*curr == ':' ||
					*curr == '&' ||
					*curr == '\\' ||
					*curr == '%' ||
					*curr == '<' ||
					*curr == '>') ? StateType::InOperator :
					*curr == '"' ? StateType::InString :
					*curr == '#' ? StateType::InComment : (
					*curr == ' ' ||
					*curr == '\n' ||
					*curr == '\r') ? StateType::Start :
					StateType::Error;
				tokenBegin = curr;
				curr++;
				break;
			case StateType::InIdentifier:
				if (!isalpha(*curr))
				{
					state = StateType::Start;
					string value(tokenBegin, curr);
					Token::Ptr token = make_shared<Token>(line, index, TokenType::Identifier, value);
					tokenStream.push_back(token);
					index--;
					break;
				}
				curr++;
				break;
			case StateType::Error:
			{
				string msg = "Error input. Can not recognize the operator.";
				Error::Ptr error = make_shared<Error>(line, index, msg);
				errorList.push_back(error);
			}
			while (*curr != ' ' || *curr != '\r' || *curr != '\n')
			{
				curr++;
				if (curr == end) break;
			}
				state = StateType::Start;
				break;


			}
		}
	}
}
