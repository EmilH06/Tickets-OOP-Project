#pragma once
#include <iostream>
#include <string>
class Ticket {
	enum class TicketStatus {
		AVAIABLE = 0,
		RESERVED = 1,
		PURCHASED = 2
	};
	const int row;
	const int seat;
	TicketStatus status;
	std::string note;
	int ID;
	static int ID_counter;
    public:
		Ticket(const int row_, const int col_,const std::string status_, const std::string note);
};