#include "LexicalExpression.h"
#include <regex>

LexicalExpression::LexicalExpression(const char* expression, bool isExpression)
{

	if (!isExpression) {

		this->expressionString = "(";
		this->expressionString.append(expression).append(")");
		this->expression = std::regex(this->expressionString);

	}
	else {

		this->expression = std::regex(expression);

	}

	this->expressionString = expression;

	int counter = 0;
	for (int i = 0; i < expressionString.length(); i++) if (expressionString[i] != '\\') counter++;

	this->expressionLength = counter;

}

bool LexicalExpression::check(const char* text)
{

	return std::regex_match(text, this->expression);

}

int LexicalExpression::getExpressionLength() {

	return this->expressionLength;

}

std::string LexicalExpression::getExpression() {

	return this->expressionString;

}