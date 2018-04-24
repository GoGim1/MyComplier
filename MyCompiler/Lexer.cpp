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

	/*Token::Vec							tokenStream;
	Error::Vec							errorList;*/

	/*void Parse(string &code)
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

		auto curr = code.begin(), end = code.end(), lineBegin = code.begin();
		string::iterator tokenBegin;
		StateType state = StateType::Start;
		int line = 0;

		while (curr != end)
		{
			if (*curr == '\n')
			{
				line++;
				lineBegin = curr + 1;
			}
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
					Token::Ptr token = make_shared<Token>(line, distance(lineBegin, tokenBegin), TokenType::Identifier, value);
					tokenStream.push_back(token);
					break;
				}
				curr++;
				break;
			case StateType::Error:
			{
				string msg = "Error input. Can not recognize the operator.";
				Error::Ptr error = make_shared<Error>(line, distance(lineBegin, tokenBegin), msg);
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
	}*/

	void Parse(string& code, Token::Vec& tokenStream)
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

		auto curr = code.begin(), end = code.end(), lineBegin = code.begin();
		string::iterator tokenBegin;
		StateType state = StateType::Start;
		int line = 0;

		while (curr != end)
		{
			if (*curr == '\n')
			{
				line++;
				lineBegin = curr + 1;
			}
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
						*curr == '\t' ||
						*curr == '\r') ? StateType::Start :
					StateType::Error;
				tokenBegin = curr;
				break;
			case StateType::End:
				break;
			case StateType::Error:
				break;
			case StateType::InInt:
				break;
			case StateType::InFloat:
				break;
			case StateType::InComment:
				break;
			case StateType::InString:
				break;
			case StateType::InIdentifier:
				if ((curr + 1) == end || !isalpha(*(curr + 1)))
				{
					state = StateType::Start;
					string value(tokenBegin, curr + 1);
					Token::Ptr token = make_shared<Token>(line, distance(lineBegin, tokenBegin), TokenType::Identifier, value);
					tokenStream.push_back(token);
				}
				break;
			case StateType::InOperator:
				break;
			default:
				break;
			}
			curr++;
		}
	}
}
