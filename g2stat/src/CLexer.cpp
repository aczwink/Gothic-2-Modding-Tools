//Class Header
#include "CLexer.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

//Lexer Tables
#include "DaedalusLexerTables.h"

//Constructor
Daedalus::CLexer::CLexer() : SJCLib::CLexer<EToken>(translateTable, transitionsTable, tokenTypeTable)
{
	this->lineNumber = 1;
}

//Private Functions
bool Daedalus::CLexer::OnNextToken(const EToken &refParsedToken)
{
	switch(refParsedToken)
	{
	case TOKEN_WHITESPACE:
		return false;
	case TOKEN_LINEFEED:
		this->lineNumber++;
		return false;
	case TOKEN_SINGLELINECOMMENT:
		//stdOut << this->GetTokenValue() << endl;
		return false;
	case TOKEN_MULTILINECOMMENT:
		repeat(this->GetTokenValue().GetLength(), i)
		{
			if(this->GetTokenValue()[i] == '\n')
				this->lineNumber++;
		}
		//stdOut << this->GetTokenValue() << endl;
		return false;
	case TOKEN_LITERAL:
		{
			this->tokenValue = this->tokenValue.SubString(1, this->tokenValue.GetLength()-2);
		}
		return true;
	}

	return true;
}