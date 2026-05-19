#pragma once
#include "Halls.h"
#include <iostream>
class Events {
	std::string Name, Date;
	Hall hall;
public:
	Events(const std::string name, const std::string date, const std::string hall_name) : Name(name), Date(date), hall(hall_name) {};
};
