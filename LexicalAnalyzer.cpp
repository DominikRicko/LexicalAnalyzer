#include <iostream>
#include <string>
#include <exception>
#include "Lexicon.h"
#include <regex>

void userPrompt(std::string& languageFilename, std::string& inputFilename, std::string& outputFilename);
void parseArguments(int argumentCount, char* arguments[], std::string& languageFilename, std::string& inputFilename, std::string& outputFilename);

int main(int argc, char* argv[]) {

	std::string languageFilename;
	std::string inputFilename;
	std::string outputFilename;

	parseArguments(argc, argv, languageFilename, inputFilename, outputFilename);

	if(argc < 7) userPrompt(languageFilename, inputFilename, outputFilename);

	try {

		Lexicon lexicon(languageFilename.c_str());
		lexicon.AnalyzeFile(inputFilename, outputFilename);

	}
	catch (std::exception& e)
	{
		
		std::cerr <<"\n\nERROR: "<< e.what() << std::endl;
		
	}

	std::cout << "\n\nAnalysis complete." << std::endl;

	return 0;
}

void parseArguments(int argumentCount, char* arguments[], std::string& languageFilename, std::string& inputFilename, std::string& outputFilename) {

	for (int i = 1; i < argumentCount; i+=2) {

		if (std::regex_match(arguments[i], std::regex("-l")))
			languageFilename = std::string(arguments[i + 1]);

		if (std::regex_match(arguments[i], std::regex("-o")))
			outputFilename = std::string(arguments[i + 1]);

		if (std::regex_match(arguments[i], std::regex("-i")))
			inputFilename = std::string(arguments[i + 1]);

	}

}

void userPrompt(std::string& languageFilename, std::string& inputFilename, std::string& outputFilename){

	if (languageFilename.empty())
	{

		std::cout << "Specify a language xml file: ";
		std::cin >> languageFilename;

	}

	if (inputFilename.empty()) 
	{

		std::cout << "Specify an input file: ";
		std::cin >> inputFilename;

	}

	if (outputFilename.empty()) 
	{

		std::cout << "Specify an output file: ";
		std::cin >> outputFilename;

	}

}