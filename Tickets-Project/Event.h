#pragma once
#include "Halls.h"
#include <iostream>
class Event {
	std::string name;
	std::string date;
	Hall hall;
public:
	Event(const std::string name, const std::string date, const std::string hall_name) : name(name), date(date), hall(hall_name) {}
	std::string getDate() const {
		return date;
	}
	std::string getHallName() const {
		return hall.getName();
	}
};
