#include "LexicalWhitelist.h"

bool LexicalWhitelist::check(const char* text)
{

    for(LexicalRule rule : this->rules)
    {
    
        if(rule.check(text)) return true;

    }

    for (const char* expression : this->expressions) 
    {

        if (text == expression) return true;

    }

    return false;

}

void LexicalWhitelist::addRule(LexicalRule rule)
{

    this->rules.push_back(rule);

}

void LexicalWhitelist::addExpression(const char* expression)
{

    this->expressions.push_back(expression);

}

LexicalWhitelist::~LexicalWhitelist() {

    this->expressions.clear();
    this->rules.clear();

}