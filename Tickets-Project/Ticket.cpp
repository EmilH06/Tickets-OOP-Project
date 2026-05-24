#include "Ticket.h"
#include <iostream>
#include <string>
int Ticket::ID_counter = 100;
Ticket::Ticket(const int currentID,const int row_, const int col_,const std::string status_,const std::string note_) : row(row_), seat(col_), note(note_){
	if (status_ == "RESERVED") {
		this->status = TicketStatus::RESERVED;
	}
	else if (status_ == "PURCHASED") {
		this->status = TicketStatus::PURCHASED;
	}
	else if (status_ == "AVAIABLE") {
		this->status = TicketStatus::AVAIABLE;
	}
	if (currentID != 0) {
		ID_counter = currentID;
	}
	ID = ID_counter;
	ID_counter++;
}
int Ticket::getID() const {
	return this->ID;
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