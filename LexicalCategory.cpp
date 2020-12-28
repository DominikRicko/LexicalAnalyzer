#include "LexicalCategory.h"
#include "LexicalExpression.h"

static bool lexicalExpressionCompareLength(LexicalExpression& a, LexicalExpression& b) {

	return a.getExpressionLength() > b.getExpressionLength();

}

static void sortExpressions(std::list<LexicalExpression>& expressionList) {
	expressionList.sort(lexicalExpressionCompareLength);
}

bool LexicalCategory::check(const char* text) 
{

	bool result = false;
	bool whitelistExists = false;

	if (!this->sorted) {

		sortExpressions(this->whitelist);
		sortExpressions(this->blacklist);
		this->sorted = true;

	}

	for (LexicalExpression expression : this->whitelist)
	{

		result |= expression.check(text);
		whitelistExists = true;
	}

	if (!result && whitelistExists) return false;

	result = true;

	for (LexicalExpression expression : this->blacklist) 
	{

		result &= !expression.check(text);

	}

	return result;
}

std::string LexicalCategory::getName() 
{

	return this->name;

}

void LexicalCategory::addExpression(LexicalExpression expression, bool isBlacklist) {

	if (isBlacklist) this->blacklist.push_back(expression);
	else this->whitelist.push_back(expression);

	this->sorted = false;

}

LexicalCategory::~LexicalCategory() {

	this->blacklist.clear();
	this->whitelist.clear();

}

LexicalCategory::LexicalCategory(std::string name, bool isSeparators) {

	this->name = name;
	this->sorted = false;
	this->isSeparators = isSeparators;

}

LexicalExpression LexicalCategory::get(unsigned int index, bool isBlacklist) {

	auto iterator = ((isBlacklist)?(this->blacklist):(this->whitelist)).begin();

	for (int counter = 0; counter < index; counter++, iterator++);

	return *iterator;

}

unsigned int LexicalCategory::getSize(bool isBlacklist) {

	return ((isBlacklist) ? (this->blacklist.size()) : (whitelist.size()));

}

bool LexicalCategory::isSeparator() {

	return this->isSeparators;

}