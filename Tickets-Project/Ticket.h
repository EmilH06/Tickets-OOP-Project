#pragma once
#include <iostream>
#include <string>
class Ticket {
    int row;
	int seat;
	std::string status;
	std::string note;
	std::string uniqueCode = "none";
    public:
		Ticket(const std::string ,const int , const int ,const std::string , const std::string );
		int getRow() const;
		int getSeat() const;
		std::string getStatus() const;
		std::string getNote() const;
		std::string getCode() const;
		void setStatus(std::string);
		void generateCode(std::string);
};