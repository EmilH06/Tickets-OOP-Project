#pragma once
#include <iostream>
#include <string>
class Ticket {
	enum class TicketStatus {
		AVAIABLE = 0,
		RESERVED = 1,
		PURCHASED = 2
	};
    int row;
	int seat;
	TicketStatus status;
	std::string note;
	int ID;
	static int ID_counter;
    public:
		Ticket(const int, const int , const int ,const std::string , const std::string );
};