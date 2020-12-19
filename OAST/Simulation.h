#pragma once
#include "Events.h"
#include "Server.h"
class Simulation {

private:
	std::unique_ptr<Server> server;
	double averageEventsNumber;
	int events_number = 10;
	float time;
	double currentTime;
	std::shared_ptr<Events_List> StartEvents(double lambda);
	double averageServiceTime;
	double mi;
	std::shared_ptr<Events_List> Events_list;
	std::shared_ptr<Events_List> Imaginary_Events_list;
	void eventHandler(std::shared_ptr<Events> event);
	void handleArrivalEvent(std::shared_ptr<Events> event);
	void handleDepartureEvent(std::shared_ptr<Events> event);
	void eventHandlerContinousService(std::shared_ptr<Events> event);
	void handleImaginaryArrival(std::shared_ptr<Events> event);
	void handleImaginaryDepartureEvent(std::shared_ptr<Events> event);
	void AddImaginaryEvent();
public:
	Simulation(double lambda, int simulationTime, float ro);
	std::vector<std::shared_ptr<Events>> Simulate();
	std::vector<std::shared_ptr<Events>> SimulateContinousService();
};