#pragma once
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iterator>

namespace Complier
{
	using namespace std;

	struct pos
	{
		int line = -1;
		int index = -1;
	};

	class Error
	{
	public:
		typedef shared_ptr<Error>	Ptr;
		typedef vector<Ptr>			Vec;

		Error(int errLine, int errIndex, string& errMsg);
		Error();
		~Error();

		pos		errorPos;
		string	errorMsg = "";
	};

	enum class TokenType
	{
		Undefine,
		Comment, 
		Reserved,
		String,
		Int,
		Float,
		Identifier,
		Symbol
	};

	class Token
	{

	public:
		typedef shared_ptr<Token>	Ptr;
		typedef vector<Ptr>			Vec;
	
		Token(int, int, TokenType, string&);
		Token();
		~Token();
			
		TokenType	type	= TokenType::Undefine;
		string		value	= "";
		pos			tokenPos;
	};

	//extern Token::Vec							tokenStream;
	//extern Error::Vec							errorList;
	//extern unordered_map<string, Token::Ptr>	symbolTable;
	
	extern void Parse(string&, Token::Vec&);

}