#pragma once
#include "Halls.h"
#include <iostream>
class Event {
	std::string name;
	std::string date;
	Hall hall;
public:
	Event(const std::string name, const std::string date, const Hall& hall_);
	Hall& getHall();
	std::string getDate() const;
	std::string getName() const;
	std::string getHallName() const;
	void addTicket(const int,const int, const int, const std::string, const std::string);
	void getFreeseats();
	void bookTicket();
};
