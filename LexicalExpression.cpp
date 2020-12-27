#include "LexicalExpression.h"
#include <regex>

LexicalExpression::LexicalExpression(const char* expression, bool blacklist)
{
	this->expressionLength = std::string(expression).length();
	this->expression = std::regex(expression);
	this->blacklist = blacklist;

}

bool LexicalExpression::check(const char* text)
{

	return this->blacklist^std::regex_match(text, this->expression);

}

std::string LexicalExpression::replace(const char* text, const char* replaceText)
{
	
	return std::regex_replace(text, this->expression, replaceText);

}

int LexicalExpression::getExpressionLength() {

	return this->expressionLength;

}