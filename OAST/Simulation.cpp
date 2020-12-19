#include "Simulation.h"
#include <random>
#include <iostream>
#include <math.h> 


Simulation::Simulation(double lambda, int simulationTime, float ro) {
	time = simulationTime;
	currentTime = 0;
	averageEventsNumber = lambda * simulationTime;
	mi = lambda / ro;
	this-> server = std::make_unique<Server>();
	Events_list = StartEvents(lambda);
	this->Imaginary_Events_list = std::make_shared<Events_List>();
	
}




std::shared_ptr<Events_List> Simulation::StartEvents(double lambda) {
	std::vector<std::shared_ptr<Events>> IncomingEvents;
	std::vector<std::shared_ptr<Events>> PastEvents;
	
	std::random_device rd;
	std::mt19937 gen(rd()); //uniform distrib 
	std::poisson_distribution<>  p_distr(averageEventsNumber); 
	auto random_events_number = p_distr(gen);
	std::exponential_distribution<> exp_dist(lambda);
	
	std::uniform_real_distribution<double> unif(0, 1);
	
	auto temp_arrival_time = 0;
	for (int i = 0; i < random_events_number; i++) {
		/*auto w = 1 - unif(gen);
		auto expo = -log(w) / lambda;*/
		auto rng = exp_dist(gen);
		auto arrival_time = temp_arrival_time + rng;
		temp_arrival_time = arrival_time;
		
		IncomingEvents.push_back(std::make_shared<Events>(arrival_time, Events::EventType::Arrival, -1));
	}
	std::sort(IncomingEvents.begin(), IncomingEvents.end(),
		[](std::shared_ptr<Events> const& a, std::shared_ptr<Events> const& b) -> bool
	{return a->event_time > b->event_time; });

	return std::make_unique<Events_List>(IncomingEvents, PastEvents);
}

std::vector<std::shared_ptr<Events>> Simulation::Simulate() {
	
	while (!Events_list->getEventsList().empty()) {
		eventHandler(Events_list->get());
	}
	return Events_list->getPastEventsList();
}
std::vector<std::shared_ptr<Events>> Simulation::SimulateContinousService() {
	while (!Events_list->getEventsList().empty()) {

		eventHandlerContinousService(Events_list->getContinousService(currentTime));
	}
	return Events_list->getPastEventsList();
}
void Simulation::eventHandler(std::shared_ptr<Events> event) {
	switch (event->event_type) {
	case Events::EventType::Arrival:
		handleArrivalEvent(event);
		break;

	case Events::EventType::Departure:
		currentTime = event->getTime();
		handleDepartureEvent(event);
		break;
	}
}

void Simulation::eventHandlerContinousService(std::shared_ptr<Events> event) {
	switch (event->event_type) {
	case Events::EventType::Arrival:
		handleArrivalEvent(event);
		break;

	case Events::EventType::Departure:
		currentTime = event->getTime();
		handleDepartureEvent(event);
		break;

	case Events::EventType::ImaginaryArrival:
		handleImaginaryArrival(event);
		break;

	case Events::EventType::ImaginaryDeparture:
		currentTime = event->getTime();
		handleImaginaryDepartureEvent(event);
		break;
	}
}
void Simulation::handleArrivalEvent(std::shared_ptr<Events> event) {
	//std::cout << "handle Arrival " << currentTime <<std::endl;
	double serviceTime;
	std::random_device rd;
	std::mt19937 gen(rd()); //uniform distrib 
	std::exponential_distribution<> exp_dist(mi);
	
	serviceTime = exp_dist(gen);
	if (server->getNumberoFClients() == 0) {
		server->addClient();
		event->setClient(server->getMaxClients());
		if (currentTime > event->getTime()) {
			Events_list->put(std::make_shared<Events>(currentTime + serviceTime, Events::EventType::Departure, event->getClient()));
		}
		else {
			Events_list->put(std::make_shared<Events>(event->getTime() + serviceTime, Events::EventType::Departure, event->getClient()));
		}
	}
	else {
		server->addClient();

		event->setClient(server->getMaxClients());
	}

}
void Simulation::handleImaginaryArrival(std::shared_ptr<Events> event) {
	double serviceTime;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::exponential_distribution<> exp_dist(mi);
	serviceTime = exp_dist(gen);
	server->addClient();
	event->setClient(server->getMaxClients());
	std::shared_ptr<Events> ImaginaryEventDeparture = std::make_shared<Events>(currentTime + serviceTime, Events::EventType::ImaginaryDeparture, server->getMaxClients());
	Imaginary_Events_list->putImaginary(ImaginaryEventDeparture);
	Events_list->put(ImaginaryEventDeparture);
}
void Simulation::AddImaginaryEvent() {
	
	std::shared_ptr<Events> ImaginaryEventArrival = std::make_shared<Events>(currentTime, Events::EventType::ImaginaryArrival, -1);
	
	Imaginary_Events_list->putImaginary(ImaginaryEventArrival);
	Events_list->put(ImaginaryEventArrival);
		
	}
	

void Simulation::handleDepartureEvent(std::shared_ptr<Events> event) {
	//std::cout << "handle Departure " << currentTime<< std::endl;
	server->removeClient();
	
}
void Simulation::handleImaginaryDepartureEvent(std::shared_ptr<Events> event) {
	//std::cout << "handle Departure " << currentTime<< std::endl;
	server->removeClient();

}
