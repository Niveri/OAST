#pragma once
#include <stdio.h>
#include <vector>
#include <memory>
class Events {

private:
	
	int client;

	
public:
	double event_time;
	enum class EventType { Arrival, Departure , ImaginaryArrival, ImaginaryDeparture};
	EventType event_type;
	Events(double time, EventType type, int client);
	void setTime(double Time);
	double getTime();
	void setType(EventType type);
	int getClient();
	void setClient(int client_num);
	EventType getType();
};

class Events_List {
private:
	std::vector<std::shared_ptr<Events>> eventsList;
	std::vector<std::shared_ptr<Events>> eventsListPast;
	std::vector<std::shared_ptr<Events>> ImaginaryEvents;
	

public:
	//bool CompareTime(std::unique_ptr<Events> const& a, std::unique_ptr<Events> const& b);
	void SortEvents(std::vector<std::shared_ptr<Events>> eventsList);
	Events_List(std::vector<std::shared_ptr<Events>> e_list, std::vector<std::shared_ptr<Events>> past_e_list);
	void put(std::shared_ptr<Events> event);
	std::shared_ptr<Events> get();
	std::shared_ptr<Events> getContinousService(const double &time);
	std::vector<std::shared_ptr<Events>> getEventsList();
	std::vector<std::shared_ptr<Events>> getPastEventsList();
	void putImaginary(std::shared_ptr<Events> event);
	Events_List();
};