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


	void Parse(string& code, Token::Vec& tokenStream, Error::Vec& errorList)
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

		auto AddToken = [](string::iterator begin, string::iterator end, TokenType type, int line, int index, Token::Vec& tokenStream)
		{
			string value(begin, end);
			Token::Ptr token = make_shared<Token>(line, index, type, value);
			tokenStream.push_back(token);
		};
		auto AddError = [](int line, int index, string& msg, Error::Vec& errorList)
		{
			Error::Ptr error = make_shared<Error>(line, index, msg);
			errorList.push_back(error);
		};

		while (curr != end)
		{
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
				if (*curr == '\n')
				{
					line++;
					lineBegin = curr + 1;
				}
				break;
			case StateType::End:
				break;
			case StateType::Error:
			if (*curr == '\n' || *curr == '\t' || *curr == '\r' || *curr  == ' ')
			{
				state = StateType::Start;
				string msg = "Can not recognize the error input. ";
				AddError(line, distance(lineBegin, tokenBegin), msg, errorList);
				curr--;
			}
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
				if (!isalpha(*curr))
				{
					state = StateType::Start;
					AddToken(tokenBegin, curr, TokenType::Identifier, line, distance(lineBegin, tokenBegin), tokenStream);
					curr--;
				}
				break;
			case StateType::InOperator:
				break;
			default:
				break;
			}
			curr++;
		}

		switch (state)
		{
		case StateType::Start:
			break;
		case StateType::End:
			break;
		case StateType::Error:
		{
			string msg = "Can not recognize the error input. ";
			AddError(line, distance(lineBegin, tokenBegin), msg, errorList);
		}
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
			AddToken(tokenBegin, end, TokenType::Identifier, line, distance(lineBegin, tokenBegin), tokenStream);
			break;
		case StateType::InOperator:
			break;
		default:
			break;
		}
	}

}
