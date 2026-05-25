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
	std::string uniqueCode = "none";
    public:
		Ticket(const std::string ,const int , const int ,const std::string , const std::string );
		int getRow() const;
		int getSeat() const;
		std::string getStatus() const;
		std::string getNote() const;
		std::string getCode() const;
};