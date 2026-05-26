#pragma once
#include "Halls.h"
#include "Ticket.h"
#include <iostream>
#include <vector>
class Event {
	std::string name;
	std::string date;
	Hall hall;
	std::vector<Ticket> list;
public:
	Event(const std::string name, const std::string date, const Hall& hall_);
	Hall& getHall();
	std::string getDate() const;
	std::string getName() const;
	std::string getHallName() const;
	std::vector<Ticket>& getList();
	void addTicket(const std::string, const int, const int, const std::string, const std::string);
	void removeTicket(const int, const int);
	void getFreeseats();
	void purchaseTicket(const std::string, const int, const int,const std::string);
};
