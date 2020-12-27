#pragma once
#include "LexicalExpression.h"
#include <list>
#include <string>

class LexicalCategory
{

public:

	LexicalCategory(const char* name);
	~LexicalCategory();

	const char* getName();
	bool check(const char* text);
	std::string identify(const char* text);
	void addExpression(LexicalExpression expression);
	

private:

	bool sorted;
	const char* name;
	std::list<LexicalExpression> expressionList;

};

