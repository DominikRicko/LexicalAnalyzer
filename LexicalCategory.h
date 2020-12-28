#pragma once
#include "LexicalExpression.h"
#include <list>
#include <string>

class LexicalCategory
{

public:

	LexicalCategory(std::string name);
	~LexicalCategory();

	std::string getName();
	bool check(const char* text);
	void addExpression(LexicalExpression expression, bool isBlacklist);
	LexicalExpression get(unsigned int index, bool isBlacklist);
	unsigned int getSize(bool isBlacklist);

private:

	bool sorted;
	std::string name;
	std::list<LexicalExpression> whitelist;
	std::list<LexicalExpression> blacklist;

};

