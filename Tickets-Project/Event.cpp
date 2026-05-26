#include "Event.h"
#include "Ticket.h"
#include <iostream>
#include <vector>
Event::Event(const std::string name, const std::string date, const Hall& hall_) : name(name), date(date), hall(hall_) {}
std::string Event::getDate() const {
	return this->date;
}
std::string Event::getName() const {
	return this->name;
}
std::string Event::getHallName() const {
	return this->hall.getName();
}
Hall& Event::getHall() {
	return this->hall;
}
std::vector<Ticket>& Event::getList() {
	return list;
}
void Event::addTicket(const std::string code,const int row, const int seat, const std::string status, const std::string note) {
	if (hall.ticketStatus(row, seat) != "AVAIABLE") {
		throw std::logic_error("This seat has already been booked!");
	}
	this->list.push_back(Ticket(code, row, seat, status, note));
	hall.saveTicket(row, seat, status);
}
void Event::removeTicket(const int row, const int col) {
	if (hall.ticketStatus(row, col) == "AVAIABLE") {
		throw std::logic_error("This seat is already avaiable!");
	}
	for (size_t i = 0; i < list.size(); i++) {
		if (list[i].getRow() == row && list[i].getSeat() == col) {
			list.erase(list.begin() + i);
			hall.saveTicket(row, col, "AVAIABLE");
			return;
		}
	}
	throw std::invalid_argument("Seat with these parameters doesn't exist!");
}
void Event::getFreeseats() {
	hall.printFreeseats();
}
void Event::purchaseTicket(const std::string date, const int row, const int seat, const std::string note) {
	if (hall.ticketStatus(row, seat) == "AVAIABLE") {
		Ticket t("none", row, seat, "PURCHASED", note);
		t.generateCode(date);
		this->list.push_back(t);
		hall.saveTicket(row, seat, "PURCHASED");
	}
	else if (hall.ticketStatus(row, seat) == "RESERVED") {
		size_t Idx = -1;
		for (size_t i = 0; i < list.size(); i++) {
			if (list[i].getRow() == row && list[i].getSeat() == seat) {
				Idx = i;
			}
		}
		list[Idx].generateCode(date);
		list[Idx].setStatus("PURCHASED");
		hall.saveTicket(row, seat, "PURCHASED");
	}
	else if (hall.ticketStatus(row, seat) == "PURCHASED") {
		throw std::logic_error("Ticket has already been purchased!");
	}
}