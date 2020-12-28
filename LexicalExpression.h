#pragma once
#include <regex>

class LexicalExpression
{

public:

	LexicalExpression(const char* expression, bool isExpression);

	bool check(const char* text);
	int getExpressionLength();
	std::string getExpression();

private:

	int expressionLength;
	std::regex expression;
	std::string expressionString;
	
};


