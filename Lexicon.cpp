#include "Lexicon.h"
#include <fstream>
#include "pugixml.hpp"

#include "LexicalCategory.h"
#include "LexicalExpression.h"

//Some black magic from 
//https://stackoverflow.com/questions/4533652/how-to-split-string-using-istringstream-with-other-delimiter-than-whitespace/44359475

std::vector<std::string> splitter(std::string in_pattern, std::string& content) {
	std::vector<std::string> split_content;

	std::regex pattern(in_pattern);
	copy(std::sregex_token_iterator(content.begin(), content.end(), pattern, -1), 
		std::sregex_token_iterator(), back_inserter(split_content));
	return split_content;
}

Lexicon::Lexicon(const char* filepath)
{
	this->maxExpressionLength = 0;

	pugi::xml_document lexicalDefinitions;
	
	if (lexicalDefinitions.load_file(filepath).status != pugi::status_ok)
		throw std::exception("Error opening language file.");
	
	pugi::xml_node separatorsNode = lexicalDefinitions.child("separators");

	for (pugi::xml_node seperator : separatorsNode)
	{

		this->separators.push_back(seperator.value());

	}

	pugi::xml_node language = lexicalDefinitions.child("language");

	for (pugi::xml_node category : language.children("category"))
	{

		LexicalCategory lexicalCategory = LexicalCategory(category.attribute("type").name());
		
		for (pugi::xml_node blacklist : category.children("blacklist")) 
		{

			for (pugi::xml_node expression : blacklist.children("expression"))
			{

				LexicalExpression lexicalExpression = LexicalExpression(expression.value(), true);
				lexicalCategory.addExpression(lexicalExpression);
			}

			for (pugi::xml_node expression : blacklist.children("string"))
			{
			
				LexicalExpression lexicalExpression = LexicalExpression('('+expression.value()+')', true);
				lexicalCategory.addExpression(lexicalExpression);

			}

		}

		for (pugi::xml_node whitelist : category.children("whitelist"))
		{

			for (pugi::xml_node expression : whitelist.children("expression"))
			{

				LexicalExpression lexicalExpression = LexicalExpression(expression.value(), false);
				lexicalCategory.addExpression(lexicalExpression);
			}

			for (pugi::xml_node expression : whitelist.children("string"))
			{

				LexicalExpression lexicalExpression = LexicalExpression('(' + expression.value() + ')', false);
				lexicalCategory.addExpression(lexicalExpression);

			}

		}

		this->categoryList.push_back(lexicalCategory);

	}

}

Lexicon::~Lexicon()
{

	this->categoryList.clear();
	this->separators.clear();

}

Lexicon::AnalysisResult Lexicon::AnalyzeFile(std::string& inputFilepath, std::string& outputFilepath)
{
	int lineCounter = 0;
	Lexicon::AnalysisResult result = Lexicon::AnalysisResult::FAILURE;

	std::string line;
	std::ifstream inputFile(inputFilepath, std::ios::in);
	std::ofstream outputFile(outputFilepath, std::ios::out);

	if (!inputFile.is_open())
		throw std::exception("Provided input file could not be opened.");

	if (!outputFile.is_open())
		throw std::exception("Provided output file could not be opened.");
	
	while (std::getline(inputFile, line))
	{
	
		std::string identifiedString = line;

		for (LexicalCategory category : this->categoryList)
			identifiedString = category.identify(identifiedString.c_str());

		lineCounter++;
		outputFile << "line " + std::to_string(lineCounter) + ": " + line;
		
		//treba podijeliti line

		outputFile << "" << std::endl;

		//lexicalUnitsCounter povečanje za bla bal
		//za svaki znak nači leksičku kategoriju te to ispisati kao "('znak', leksička_kategorija)\n"
		//std::string word = line.substr();

	}
	
	inputFile.close();
	outputFile.close();

	return result;

}