#pragma once
#include "Ticket.h"
#include <iostream>
#include <vector>
#include <string>
class Hall {
	std::string name;
	std::vector<Ticket> list;
	const int rows, cols;
public:
	Hall(const std::string name_) : name(name_) , rows(0), cols(0) {};
};
