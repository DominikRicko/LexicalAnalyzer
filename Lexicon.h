#pragma once
#include <string>
#include <list>
#include "LexicalCategory.h"

class Lexicon
{
	
public:
	Lexicon(const char* filepath);
	~Lexicon();
	
	void AnalyzeFile(std::string& inputFilepath, std::string& outputFilepath);

private:
	
	std::list<LexicalCategory> categoryList;

};

