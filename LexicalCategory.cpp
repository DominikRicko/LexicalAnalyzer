#include "LexicalCategory.h"
#include "LexicalExpression.h"

static bool lexicalExpressionCompareLength(LexicalExpression& a, LexicalExpression& b) {

	return a.getExpressionLength() > b.getExpressionLength();

}

static bool sortExpressions(std::list<LexicalExpression>& expressionList) {
	expressionList.sort(lexicalExpressionCompareLength);
}

bool LexicalCategory::check(const char* text) 
{

	bool result = true;

	if (!this->sorted) {

		sortExpressions(this->expressionList);
		this->sorted = true;

	}

	for (LexicalExpression expression : this->expressionList)
	{

		result &= expression.check(text);

	}

	return result;
}

const char* LexicalCategory::getName() 
{

	return this->name;

}

void LexicalCategory::addExpression(LexicalExpression expression) {

	this->expressionList.push_back(expression);
	this->sorted = false;

}

std::string LexicalCategory::identify(const char* text)
{

	std::string tempText(text);

	if (!this->sorted) {

		sortExpressions(this->expressionList);
		this->sorted = true;

	}

	for (LexicalExpression expression : this->expressionList)
	{

		tempText = expression.replace(tempText.c_str(), ' ' + (this->name) + ' ');

	}

	return tempText;

}

LexicalCategory::~LexicalCategory() {
}

LexicalCategory::LexicalCategory(const char* name) {

	this->name = name;
	this->sorted = false;

}