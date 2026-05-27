#include "Ticket.h"
#include <iostream>
#include <string>
Ticket::Ticket(const std::string code,const int row_, const int col_, const std::string status_, const std::string note_) : row(row_), seat(col_), note(note_),uniqueCode(code) {
	if (status_ == "AVAIABLE" || status_ == "RESERVED" || status_ == "PURCHASED") {
		status = status_;
	}
	else {
		throw std::invalid_argument("Invalid ticket status!");
	}
}
int Ticket::getRow() const {
	return this->row;
}
int Ticket::getSeat() const {
	return this->seat;
}
std::string Ticket::getStatus() const {
	return this->status;
}
std::string Ticket::getNote() const {
	return this->note;
}
std::string Ticket::getCode() const {
	return uniqueCode;
}
void Ticket::setStatus(std::string other_status) {
	status = other_status;
}
void Ticket::generateCode(std::string name,std::string date) {
	for (int i = 0; i < date.size(); i++) {
		if (date[i] == '-') { date.erase(i, 1); i--; }
	}
	for (int i = 0; i < name.size(); i++) {
		if (name[i] == ' ') { name.erase(i, 1); i--; }
	}
	uniqueCode = date + name + std::to_string(row)+"-"+std::to_string(seat);
}