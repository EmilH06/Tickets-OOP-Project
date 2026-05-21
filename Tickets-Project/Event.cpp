#include "Event.h"
#include <iostream>
Event::Event(const std::string name, const std::string date, const std::string hall_name) : name(name), date(date), hall(hall_name) {}
std::string Event::getDate() const {
	return date;
}
std::string Event::getName() const {
	return name;
}
std::string Event::getHallName() const {
	return hall.getName();
}
void Event::addTicket(const std::string row, const std::string seat, const std::string status, const std::string note) {
	hall.getList().push_back(Ticket(std::stoi(row), std::stoi(seat), status, note));
}