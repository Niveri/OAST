#pragma once
#include <string>
#include "Events.h"
class Results {
private:
	std::string filename;
	void WriteResultsToFile(std::string filename, std::string results);
public:
	Results(std::string file);
	void genResultsContinousService(double ro, std::vector<std::vector<std::shared_ptr<Events>>> eventsVector, int waitTime);
	void genResults(double ro, std::vector<std::vector<std::shared_ptr<Events>>> eventsVector, int waitTime);
	double calculateAverageClientTimeInSystem(std::vector<std::shared_ptr<Events>> eventsVector);
	double ImaginaryClientProbabilty(std::vector<std::shared_ptr<Events>> eventsVector);
	//void calculateAverageClientTimeInSystem(std::vector<std::shared_ptr<Events>> eventsVector);
};