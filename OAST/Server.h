#pragma once
class Server {
private:
	int number_of_clients;
	int max_clients;

public:
	//void Server() {};

	Server();
	void addClient();
	void removeClient();
	int getNumberoFClients();
	int getMaxClients();
};
