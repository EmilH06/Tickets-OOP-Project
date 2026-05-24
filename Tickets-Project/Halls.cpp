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
	void Hall::saveTicket(const int row, const int col,const TicketStatus status) {
		int rowIdx = row - 1;
		int colIdx = col - 1;
		if(rowIdx<0 || rowIdx>=this->rows || colIdx<0 || colIdx>=this->cols)
		seats[rowIdx][colIdx] = status;
	}