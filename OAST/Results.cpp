#include"Results.h"
#include<map>
#include<iostream>
#include <fstream>


Results::Results(std::string file) {
	this->filename = file;
}
void Results::WriteResultsToFile(std::string filename, std::string results) {
	std::ofstream file;
	file.open(filename);
	file << results;

	file.close();


}
double Results::calculateAverageClientTimeInSystem(std::vector<std::shared_ptr<Events>> eventsVector) {
	std::map<int, double> serviceTimeMap;
	for (std::shared_ptr<Events> const& event : eventsVector) {
		if (event->getType() == Events::EventType::Arrival) {
			serviceTimeMap.emplace(event->getClient(), event->getTime());
		}
		else if (event->getType() == Events::EventType::Departure) {
			std::map<int, double>::iterator it = serviceTimeMap.find(event->getClient());
			if (it != serviceTimeMap.end())
				it->second = event->getTime() - it->second;
		}
	}
	double sum = 0;
	for (auto iterator = serviceTimeMap.begin(); iterator != serviceTimeMap.end(); iterator++) {
		sum += iterator->second;
	}
	double avgDelay = sum / serviceTimeMap.size();
	return avgDelay;
}

double Results::ImaginaryClientProbabilty(std::vector<std::shared_ptr<Events>> eventsVector) {
	int ImaginaryClientsNumber = 0;
	int NormalClientsNumber = 0;
	for (auto& event : eventsVector) {
		if (event->getType() == Events::EventType::ImaginaryArrival) {
			ImaginaryClientsNumber++;
		}
		else if (event->getType() == Events::EventType::Arrival) {
			NormalClientsNumber++;
		}
	}
	
	double substract = ImaginaryClientsNumber + NormalClientsNumber;
	double ImaginaryClientProbability = ImaginaryClientsNumber / substract;
	return ImaginaryClientProbability;
}
void Results::genResultsContinousService(double ro, std::vector<std::vector<std::shared_ptr<Events>>> eventsVector, int waitTime) {
	std::string result = std::to_string(ro) + "\n";;
	std::string avgTime;
	std::cout << "ro " << ro << std::endl;
	for (auto& x : eventsVector) {
		
		//std::cout<< calculateAverageClientTimeInSystem(x)<< "  ";
		std::cout << ImaginaryClientProbabilty(x) << "   ";
		result += std::to_string(ImaginaryClientProbabilty(x));
		result += "\n";
		avgTime += std::to_string(calculateAverageClientTimeInSystem(x));
		avgTime += "\n";
		/*for (auto& y : x) {
			if (y->getType() == Events::EventType::Arrival) {
				std::cout <<"client number: "<<y->getClient() << "  " << "Arrival " << y->getTime() << std::endl;;
			}
			else if(y->getType() == Events::EventType::Departure){
				std::cout << "client number: " << y->getClient()<<"  "<<"Departure " << y->getTime() << std::endl;
			}
			if (y->getType() == Events::EventType::ImaginaryArrival) {
				std::cout << "client number: " << y->getClient() << "  " << "ImaginaryArrival " << y->getTime() << std::endl;;
			}
			else if (y->getType() == Events::EventType::ImaginaryDeparture) {
				std::cout << "client number: " << y->getClient() << "  " << "ImaginaryDeparture " << y->getTime() << std::endl;
			}
		}*/
	}
	WriteResultsToFile("zad2" + std::to_string(ro) + ".txt", result);
	WriteResultsToFile("zad2avgtime" + std::to_string(ro) + ".txt", avgTime);


}
void Results::genResults(double ro, std::vector<std::vector<std::shared_ptr<Events>>> eventsVector, int waitTime) {
	std::string result =std::to_string(ro) + "\n";
	std::cout << "ro " << ro << std::endl;
	for (auto &x : eventsVector) {
		std::cout<< calculateAverageClientTimeInSystem(x)<< "  ";
		result += std::to_string(calculateAverageClientTimeInSystem(x));
		result += "\n";

		/*for (auto& y : x) {
			if (y->getType() == Events::EventType::Arrival) {
				std::cout << "client number: " << y->getClient() << "  " << "Arrival " << y->getTime() << std::endl;;
			}
			else if (y->getType() == Events::EventType::Departure) {
				std::cout << "client number: " << y->getClient() << "  " << "Departure " << y->getTime() << std::endl;
			}
		}*/
		
	}
	WriteResultsToFile("zad1"+ std::to_string(ro)+".txt", result);

}
