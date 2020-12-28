#include "OccuranceCounter.h"
#include<string>
#include<regex>

OccuranceCounter::OccuranceCounter() {
}

OccuranceCounter::~OccuranceCounter() {

	this->category.clear();
	this->counters.clear();
	this->watchedStrings.clear();

}

int OccuranceCounter::getOccuranceCount(unsigned int index) {

	return counters.at(index);

}

int OccuranceCounter::getOccurnaceCount(std::string whatString) {

	for (int i = 0; i < this->counters.size(); i++)
		if (this->watchedStrings.at(i) == whatString)
			return i;


	return -1;

}

bool OccuranceCounter::observe(std::string whatString) {

	for (int i = 0; i < this->watchedStrings.size(); i++) {

		if (this->watchedStrings.at(i) == whatString) {
			this->counters.at(i)++;
			return true;
		}

	}

	return false;


}

void OccuranceCounter::addString(std::string whatString, unsigned int occurnaces, std::string whatCategory) {

	this->watchedStrings.push_back(whatString);
	this->counters.push_back(occurnaces);
	this->category.push_back(whatCategory);

}

std::vector<std::pair<std::string, unsigned int>> OccuranceCounter::getCategoryStrings(std::string categoryName) {

	std::vector<std::pair<std::string, unsigned int>> filteredData;

	for (int i = 0; i < watchedStrings.size(); i++) {

		if (std::regex_match(category[i],std::regex(categoryName))) {

			std::pair<std::string, unsigned int> dataPair(watchedStrings.at(i),counters.at(i));
			filteredData.push_back(dataPair);

		}

	}

	return filteredData;

}
