#include "Lexicon.h"
#include <fstream>
#include "pugixml.hpp"

#include "LexicalCategory.h"
#include "LexicalExpression.h"


static LexicalCategory findSeparators(std::list<LexicalCategory> categories) {

	for (auto category : categories) {

		if (category.isSeparator()) {

			return category;

		}

	}

	LexicalCategory defaultSeparators("separator", true);
	LexicalExpression defaultSeparator(" ", false);
	defaultSeparators.addExpression(defaultSeparator,false);
	return defaultSeparators;

}

static std::list<std::string> splitter(LexicalCategory& separators, std::string content) {

	//Iteratori ne mogu ovaj kompleksni zadatak napraviti, a i gubi se informacija o kojem seperatoru je riječ
	//napraviti strukturu i u njoj tr...
	//ustvari, napraviti ovo, ali nakon svake iteracije staviti seperatore u vektor između elemenata vektora

	std::list<std::string> split_content;
	
	for (unsigned int contentIndex = 0; contentIndex < content.length(); contentIndex++) {

		for (unsigned int i = 0; i < separators.getSize(false); i++) {

			LexicalExpression separator = separators.get(i, false);

			std::string checkString = content.substr(contentIndex, separator.getExpressionLength());

			if (separator.check(checkString.c_str())) {

				std::string word = content.substr(0, contentIndex);
				split_content.push_back(word);
				split_content.push_back(checkString);
				content = content.substr(contentIndex + separator.getExpressionLength(), content.length() - 1);
				contentIndex = 0;
			}

		}

	}

	return split_content;
}

Lexicon::Lexicon(const char* filepath)
{
	pugi::xml_document lexicalDefinitions;
	
	if (lexicalDefinitions.load_file(filepath).status != pugi::status_ok)
		throw std::exception("Error opening language file.");

	pugi::xml_node language = lexicalDefinitions.child("language");

	for (pugi::xml_node category : language.children("category"))
	{

		LexicalCategory lexicalCategory = LexicalCategory(category.attribute("type").value(),category.attribute("separators").as_bool());
		
		for (pugi::xml_node blacklist : category.children("blacklist")) 
		{

			for (pugi::xml_node expression : blacklist.children("expression"))
			{

				for (auto expressionNode : expression) {

					LexicalExpression lexicalExpression = LexicalExpression(expressionNode.text().as_string(), true);
					lexicalCategory.addExpression(lexicalExpression,true);

				}
			}

			for (pugi::xml_node expression : blacklist.children("string"))
			{
			
				for (auto expressionNode : expression) {

					LexicalExpression lexicalExpression = LexicalExpression(expressionNode.text().as_string(), false);
					lexicalCategory.addExpression(lexicalExpression,true);

				}
			}

		}

		for (pugi::xml_node whitelist : category.children("whitelist"))
		{

			for (pugi::xml_node expression : whitelist.children("expression"))
			{

				for (auto expressionNode : expression) {

					LexicalExpression lexicalExpression = LexicalExpression(expressionNode.text().as_string(), true);
					lexicalCategory.addExpression(lexicalExpression,false);

				}
			}

			for (pugi::xml_node expression : whitelist.children("string"))
			{
				for (auto expressionNode : expression) {

					LexicalExpression lexicalExpression = LexicalExpression(expressionNode.text().as_string(), false);
					lexicalCategory.addExpression(lexicalExpression,false);

				}

			}

		}

		this->categoryList.push_back(lexicalCategory);

	}

}

Lexicon::~Lexicon()
{

	this->categoryList.clear();

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
	
	LexicalCategory separators = findSeparators(this->categoryList);

	while (std::getline(inputFile, line))
	{

		std::list<std::string> separatedStrings(splitter(separators, line));

		lineCounter++;
		outputFile << "line " + std::to_string(lineCounter) + ": " + line << std::endl;

		for (auto word : separatedStrings) {

			bool foundCategory = false;

			for (LexicalCategory category : this->categoryList) {

				if (category.check(word.c_str())) {

					outputFile << "(\'" << word <<"\', " << category.getName() << ")" << std::endl;
					foundCategory = true;
				}

			}

			if (!foundCategory) {

				outputFile << "(\'" << word << "\', " << "unknown or value" << ")" << std::endl;
			}
				
		}

		//lexicalUnitsCounter povečanje za bla bal
		//za svaki znak nači leksičku kategoriju te to ispisati kao "('znak', leksička_kategorija)\n"
		//std::string word = line.substr();

	}
	
	inputFile.close();
	outputFile.close();

	return result;

}