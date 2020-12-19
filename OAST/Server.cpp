#include "Server.h"
#include<iostream>

Server::Server() {
	number_of_clients = 0;
	max_clients = 0;
}
void Server::addClient() {
	number_of_clients++;
	max_clients++;
	//std::cout << "client added! number of clients:" << number_of_clients;
}
void Server::removeClient() {
	number_of_clients--;
	//std::cout << "client removed! number of clients:" << number_of_clients;
}
int Server::getNumberoFClients() {
	return number_of_clients;
}
int Server::getMaxClients() {
	return max_clients;
}