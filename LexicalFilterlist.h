#pragma once
#include <list>
#include "LexicalRule.h"

class LexicalFilterlist
{
public:
	
	virtual bool check(const char* text) = 0;
	virtual void addRule(LexicalRule rule) = 0;
	virtual void addExpression(const char* expression) = 0;

protected:

	std::list<const char*> strings;
	std::list<LexicalRule> expressions;

};

