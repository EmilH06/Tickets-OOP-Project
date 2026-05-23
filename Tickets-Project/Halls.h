#pragma once
#include "Ticket.h"
#include <iostream>
#include <vector>
#include <string>
class Hall {
	enum class TicketStatus {
		AVAIABLE = 0,
		RESERVED = 1,
		PURCHASED = 2
	};
	const std::string name;
	std::vector<std::vector<TicketStatus>> seats;
	std::vector<Ticket> list;
	int rows = 0;
	int cols = 0;
public:
	Hall(const std::string name_, const int, const int);
	std::vector<Ticket>& getList();
	std::string getName() const;
	void saveTicket(const int, const int, const TicketStatus);
};
