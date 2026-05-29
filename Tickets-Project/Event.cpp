#include "Event.h"
#include "Ticket.h"
#include <iostream>
#include <vector>
Event::Event(const std::string name, const std::string date, const Hall hall_) : name(name), date(date), hall(hall_) {}
Event::Event(const Event& other) {
	*this = other;
}
std::string Event::getDate() const {
	return this->date;
}
std::string Event::getName() const {
	return this->name;
}
std::string Event::getHallName() const {
	return this->hall.getName();
}
std::vector<Ticket> Event::getList() {
	return this->list;
}
void Event::addTicket(const std::string code,const int row, const int seat, const std::string status, const std::string note) {
	if (hall.getTicketStatus(row, seat) != "AVAIABLE") {
		throw std::logic_error("This seat has already been booked!");
	}
	this->list.push_back(Ticket(code, row, seat, status, note));
	hall.saveTicket(row, seat, status);
}
void Event::removeTicket(const int row, const int col) {
	if (hall.getTicketStatus(row, col) == "AVAIABLE") {
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
void Event::getBookedSeats() {
		hall.printBookedSeats();
}
bool Event::getAttendence(const std::string from, const std::string to) {
	if (from <= date && date <= to) {
		double percent = (this->list.size() / (hall.getRows() * hall.getCols())) * 100;
		if (percent <= 10.00) {
			return true;
			std::cout << "Event: " << name << '\n';
			std::cout << "Attendence: " << percent << '\n';
		}
	}
	std::cout << std::endl;
	return false;
}
bool Event::checkCode(const std::string& code) {
	if (code == "none") {
		throw std::logic_error("Invalid ticket code");
	}
	for (Ticket& t : list) {
		if (t.getCode() == code) {
			std::cout << "Row: " << t.getRow() << ' ' << "Seat: " << t.getSeat() << std::endl;
			return true;
		}
	}
	return false;
}
void Event::getReport(const std::string from,const std::string to) {
	if (from <= date && date <= to) {
		std::cout << "Performance:" << '\n';
		std::cout << "Name: " << name << '\n';
		std::cout << "Date: " << date << '\n';
		std::cout << "Tickets sold: " << list.size();
		std::cout << std::endl;
	}
}
void Event::purchaseTicket(const std::string name,const std::string date, const int row, const int seat, const std::string note) {
	if (hall.getTicketStatus(row, seat) == "AVAIABLE") {
		Ticket t("none", row, seat, "PURCHASED", note);
		t.generateCode(name,date);
		this->list.push_back(t);
		hall.saveTicket(row, seat, "PURCHASED");
	}
	else if (hall.getTicketStatus(row, seat) == "RESERVED") {
		size_t Idx = -1;
		for (size_t i = 0; i < list.size(); i++) {
			if (list[i].getRow() == row && list[i].getSeat() == seat) {
				Idx = i;
			}
		}
		list[Idx].generateCode(name,date);
		list[Idx].setStatus("PURCHASED");
		hall.saveTicket(row, seat, "PURCHASED");
	}
	else if (hall.getTicketStatus(row, seat) == "PURCHASED") {
		throw std::logic_error("Ticket has already been purchased!");
	}
}
Event& Event::operator=(const Event& other) {
	if (this == &other) {
		return *this;
	}
	this->name = other.name;
	this->date = other.date;
	this->hall = other.hall;
	this->list = other.list;
	return *this;
}