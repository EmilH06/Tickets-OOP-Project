#include "Halls.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
Hall::Hall(const std::string name_, const int row_, const int col_) : name(name_), rows(row_), cols(col_) {
	seats.resize(rows, std::vector<TicketStatus>(cols, TicketStatus::AVAIABLE));
}
	std::string Hall::getName() const {
		return this->name;
	}
	std::vector<Ticket>& Hall::getList() {
		return this->list;
	}
	void Hall::saveTicket(const int row, const int col,const std::string status) {
		int rowIdx = row - 1;
		int colIdx = col - 1;
		if (rowIdx < 0 || rowIdx >= this->rows || colIdx < 0 || colIdx >= this ->cols) {
			throw std::invalid_argument("This row or seat doesn't exist!");
		}
		if (status == "AVAIABLE") {
			seats[rowIdx][colIdx] = TicketStatus::AVAIABLE;
		}
		else if (status == "RESERVED") {
			seats[rowIdx][colIdx] = TicketStatus::RESERVED;
		}
		else if (status == "PURCHASED") {
			seats[rowIdx][colIdx] = TicketStatus::PURCHASED;
		}
		else { throw std::invalid_argument("Incorrect ticket status input!"); }
	}
	void Hall::printFreeseats() {
		bool foundAvaiable = false;
		for (size_t i = 0; i < seats.size(); i++) {
			bool foundBySeat = false;
			std::cout << "Row " << i + 1 << std::endl;
			std::cout << "Seats: ";
			for (size_t j = 0; j < seats[i].size(); j++) {
				if (seats[i][j] == TicketStatus::AVAIABLE) {
					foundAvaiable = true;
					foundBySeat = true;
					std::cout << j + 1;
					if (j != seats[i].size() - 1) { std::cout << ", "; }
				}
			}
			if (!foundBySeat) {
				std::cout << "None";
			}
			std::cout << std::endl;
		}
		if (!foundAvaiable) {
			std::cout << "No seats are avaiable!" << std::endl;;
		}
	}