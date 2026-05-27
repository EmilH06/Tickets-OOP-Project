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
	int rows = 0;
	int cols = 0;
public:
	Hall(const std::string name_, const int, const int);
	std::string getName() const;
	int getRows() const;
	int getSeats() const;
	void printByStatus(const TicketStatus);
	void saveTicket(const int, const int, const std::string status);
	void printFreeseats();
	void printBookedSeats();
	std::string getTicketStatus(const int, const int);
};
