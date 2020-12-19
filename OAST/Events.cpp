#include "Events.h"
#include <algorithm>

Events::Events(double time, EventType type, int client =-1) {
	event_time = time;
	event_type = type;
	this->client = client;
}

void Events::setTime(double time) {
	event_time = time;

}
double Events::getTime() {
	return event_time;
}
void Events::setType(EventType type) {
	event_type = type;

}
void Events::setClient(int client_num){
	client = client_num;
}
int Events::getClient() {
	return client;
}

Events_List::Events_List() {

}
Events::EventType Events::getType() {
	return event_type;
}
bool CompareTime(std::shared_ptr<Events> const &a, std::shared_ptr<Events> const &b) {
	return a->event_time > b->event_time;
}
void Events_List::SortEvents(std::vector<std::shared_ptr<Events>> eventsList) {
	std::sort(eventsList.begin(), eventsList.end(), CompareTime);
}
Events_List::Events_List(std::vector<std::shared_ptr<Events>> e_List, std::vector<std::shared_ptr<Events>> past_e_list) {
	this->eventsList = e_List;
	this->eventsListPast = past_e_list;
	SortEvents(eventsList);
	SortEvents(past_e_list);
}
void Events_List::put(std::shared_ptr<Events> event) {
	this->eventsList.push_back(event);
	SortEvents(this->eventsList);

}
void Events_List::putImaginary(std::shared_ptr<Events> event) {
	this->ImaginaryEvents.push_back(event);
	SortEvents(this->ImaginaryEvents);

}
std::shared_ptr<Events> Events_List::get() {
	std::shared_ptr<Events> event = std::move(eventsList.back());
	this->eventsList.pop_back();
	this->eventsListPast.push_back(event);
	return event;

}
std::shared_ptr<Events> Events_List::getContinousService(const double& time) {
	if (eventsList.back()->getTime() > time && eventsList.back()->getType()==Events::EventType::Arrival && time!=0) {
		std::shared_ptr<Events> ImaginaryEventArrival = std::make_shared<Events>(time, Events::EventType::ImaginaryArrival, -1);
		this->eventsListPast.push_back(ImaginaryEventArrival);
		return ImaginaryEventArrival;
	}
	else {
		std::shared_ptr<Events> event = std::move(eventsList.back());
		this->eventsList.pop_back();
		this->eventsListPast.push_back(event);
		return event;
	}
}

std::vector<std::shared_ptr<Events>> Events_List::getEventsList() {
	if (eventsList.empty()) {
		return {};
	}
	return this->eventsList;
}
std::vector<std::shared_ptr<Events>> Events_List::getPastEventsList() {
	
	if (eventsListPast.empty()) {
		return {};
	}
	return this->eventsListPast;
}