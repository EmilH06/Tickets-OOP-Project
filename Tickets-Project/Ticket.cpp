#include "Ticket.h"
#include <iostream>
#include <string>
Ticket::Ticket(const std::string code,const int row_, const int col_, const std::string status_, const std::string note_) : row(row_), seat(col_), note(note_),uniqueCode(code) {
	if (status_ == "RESERVED") {
		this->status = TicketStatus::RESERVED;
	}
	else if (status_ == "PURCHASED") {
		this->status = TicketStatus::PURCHASED;
	}
	else if (status_ == "AVAIABLE") {
		this->status = TicketStatus::AVAIABLE;
	}
}
int Ticket::getRow() const {
	return this->row;
}
int Ticket::getSeat() const {
	return this->seat;
}
std::string Ticket::getStatus() const {
	switch (this->status) {
	case TicketStatus::AVAIABLE: return "AVAIABLE";
	case TicketStatus::RESERVED: return "RESERVED";
	case TicketStatus::PURCHASED: return "PURCHASED";
	}
}
std::string Ticket::getNote() const {
	return this->note;
}
std::string Ticket::getCode() const {
	return uniqueCode;
}