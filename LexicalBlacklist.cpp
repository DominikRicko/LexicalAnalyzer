#include "LexicalBlacklist.h"

bool LexicalBlacklist::check(const char* text)
{

    for (LexicalRule rule : this->rules)
    {

        if (rule.check(text)) return false;

    }

    for (const char* expression : this->expressions)
    {

        if (text == expression) return false;

    }

    return true;

}

void LexicalBlacklist::addRule(LexicalRule rule)
{

    this->rules.push_back(rule);

}

void LexicalBlacklist::addExpression(const char* expression)
{

    this->expressions.push_back(expression);

}

LexicalBlacklist::~LexicalBlacklist() {

    this->expressions.clear();
    this->rules.clear();

}

LexicalBlacklist::LexicalBlacklist() {}