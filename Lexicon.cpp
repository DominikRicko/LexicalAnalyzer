#include "Lexicon.h"
#include <fstream>
#include "pugixml.hpp"

#include "LexicalCategory.h"
#include "LexicalExpression.h"
#include "OccuranceCounter.h"

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

	std::list<std::string> split_content;
	bool noSplit = true;
	
	for (unsigned int contentIndex = 0; contentIndex < content.length(); contentIndex++) {

		bool noSplit = true;

		for (unsigned int i = 0; i < separators.getSize(false); i++) {

			LexicalExpression separator = separators.get(i, false);

			std::string checkString = content.substr(contentIndex, separator.getExpressionLength());

			if (separator.check(checkString.c_str())) {

				std::string word = content.substr(0, contentIndex);

				if (!word.empty()) split_content.push_back(word);

				split_content.push_back(checkString);
				content = content.substr(contentIndex + separator.getExpressionLength(), content.length() - 1);
				contentIndex = 0;
				noSplit = false;
			}

		}

	}

	if (noSplit && !content.empty()) split_content.push_back(content);

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

void Lexicon::AnalyzeFile(std::string& inputFilepath, std::string& outputFilepath)
{
	int lineCounter = 0;
	std::string line;
	std::ifstream inputFile(inputFilepath, std::ios::in);
	std::ofstream outputFile(outputFilepath, std::ios::out);
	OccuranceCounter occuranceCounter;

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
					if(!occuranceCounter.observe(word)) 
						occuranceCounter.addString(word, 1, category.getName());

				}

			}

			if (!foundCategory) {

				outputFile << "(\'" << word << "\', " << "unknown or value" << ")" << std::endl;
				if (!occuranceCounter.observe(word))
					occuranceCounter.addString(word, 1, "unknown");
			}
				
		}
		outputFile << std::endl;

	}

	outputFile << std::endl;

	for (auto category : categoryList) {

		auto categorizedStrings = occuranceCounter.getCategoryStrings(category.getName());

		outputFile << std::endl << "- " << category.getName() << " [";
		unsigned int count = 0;

		for (auto dataPair : categorizedStrings) 	
			count += dataPair.second;

		outputFile << count << "]:";
		
		for (auto dataPair : categorizedStrings) {

			outputFile << " \'" << dataPair.first << "\' [" << dataPair.second << "],";

		}

		outputFile << std::endl;

	}
	
	auto categorizedStrings = occuranceCounter.getCategoryStrings("unknown");

	outputFile << std::endl << "- " << "unknown" << " [";
	unsigned int count = 0;

	for (auto dataPair : categorizedStrings)
		count += dataPair.second;

	outputFile << count << "]:";

	for (auto dataPair : categorizedStrings) {

		outputFile << " \'" << dataPair.first << "\' [" << dataPair.second << "],";

	}

	outputFile << std::endl;

	inputFile.close();
	outputFile.close();

}