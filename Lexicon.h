#pragma once
#include <string>
#include <list>
#include "LexicalCategory.h"

class Lexicon
{
	
public:
	Lexicon(const char* filepath);
	~Lexicon();
	
	enum class AnalysisResult 
	{ 
		FAILURE = false, 
		SUCCESS = true
	};

	AnalysisResult AnalyzeFile(std::string& inputFilepath, std::string& outputFilepath);

private:
	
	std::list<std::string> separators;
	std::list<LexicalCategory> categoryList;
	int maxExpressionLength;

};

