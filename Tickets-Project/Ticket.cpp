#include "Ticket.h"
#include <iostream>
#include <string>
int Ticket::ID_counter = 100;
Ticket::Ticket(const int currentID,const int row_, const int col_,const std::string status_,const std::string note_) : row(row_), seat(col_), note(note_){
	if (status_ == "RESERVED") {
		status = TicketStatus::RESERVED;
	}
	else if (status_ == "PURCHASED") {
		status = TicketStatus::PURCHASED;
	}
	else if (status_ == "AVAIABLE") {
		status = TicketStatus::AVAIABLE;
	}
	ID_counter = currentID;
	ID = ID_counter;
	ID_counter++;
}