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
	std::string name;
	std::vector<std::vector<TicketStatus>> seats;
	int rows = 0;
	int cols = 0;
public:
	Hall() = default;
	Hall(const std::string name_, const int, const int);
	Hall(const Hall& other);
	std::string getName() const;
	int getRows() const;
	int getCols() const;
	void printByStatus(const TicketStatus&) const;
	void saveTicket(const int&, const int&, const std::string& status);
	void printFreeseats() const;
	void printBookedSeats() const;
	std::string getTicketStatus(const int&, const int&);
	Hall& operator=(const Hall& other);
	~Hall() = default;
};
