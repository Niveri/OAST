// OAST.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "Simulation.h"
#include "Results.h"

void Part1() {
	int simulation_time = 50;
	float lambda = 1;
	int repeat_number = 40;
	float ro = 0.25;
	
	std::unique_ptr<Results> results = std::make_unique<Results>("plik");
	while (ro <= 0.75) {
		std::vector<std::vector<std::shared_ptr<Events>>> eventsListPast;
		for (int i = 0; i < repeat_number; i++) {
			std::unique_ptr<Simulation> simulation = std::make_unique<Simulation>(lambda, simulation_time, ro);
			eventsListPast.push_back(simulation->Simulate());
		}
		results->genResults(ro, eventsListPast, 4);
		ro += 0.25;
	}
}


void Part2() {
	int simulation_time = 50;
	float lambda = 1;
	int repeat_number = 40;
	float ro = 0.25;
	
	std::unique_ptr<Results> results = std::make_unique<Results>("plik2");
	while (ro <= 0.75) {
		std::vector<std::vector<std::shared_ptr<Events>>> eventsListPast;
		for (int i = 0; i < repeat_number; i++) {
			std::unique_ptr<Simulation> simulation = std::make_unique<Simulation>(lambda, simulation_time, ro);
			eventsListPast.push_back(simulation->SimulateContinousService());
		}
		results->genResultsContinousService(ro, eventsListPast, 4);
		ro += 0.25;
	}
}


int main()
{
	Part1();
	Part2();

}
