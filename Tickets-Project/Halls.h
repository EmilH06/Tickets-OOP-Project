#pragma once
#include "Ticket.h"
#include <iostream>
#include <vector>
#include <string>
class Hall {
	const std::string name;
	std::vector<std::vector<int>> seats;
	std::vector<Ticket> list;
	int rows = 0;
	int cols = 0;
public:
	Hall(const std::string name_);
	std::string getName() const;
};
