#include <iostream>
#include "Simulation.h"
int main()
{	
	auto simulation_time = 100;
	auto lambda = 0.5;
	std::unique_ptr<Simulation> simulation = std::make_unique<Simulation>(lambda, simulation_time);

}