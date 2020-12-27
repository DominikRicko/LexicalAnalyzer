#pragma once
#include <regex>

class LexicalExpression
{

public:

	LexicalExpression(const char* expression, bool blacklist);

	bool check(const char* text);
	std::string replace(const char* text, const char* replaceText);
	
	int getExpressionLength();
private:

	int expressionLength;
	bool blacklist;
	std::regex expression;
	
};


