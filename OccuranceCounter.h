#pragma once
#include<vector>
#include<string>

class OccuranceCounter {

public:

	OccuranceCounter();
	~OccuranceCounter();

	int getOccuranceCount(unsigned int index);
	int getOccurnaceCount(std::string whatString);

	bool observe(std::string whatString);
	void addString(std::string whatString, unsigned int occurnaces, std::string whatCategory);
	std::vector<std::pair<std::string, unsigned int>> getCategoryStrings(std::string categoryName);

private:

	std::vector<std::string> watchedStrings;
	std::vector<unsigned int> counters;
	std::vector<std::string> category;

};