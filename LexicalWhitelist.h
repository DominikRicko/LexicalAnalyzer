#pragma once
#include "LexicalFilterlist.h"

class LexicalWhitelist : public LexicalFilterlist
{

public:
	// Inherited via Filterlist
	virtual bool check(const char* text) override;	
	virtual void addRule(LexicalRule rule) override;
	virtual void addExpression(const char* expression) override;

	LexicalWhitelist();
	~LexicalWhitelist();

};

