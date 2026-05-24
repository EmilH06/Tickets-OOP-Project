#include "Event.h"
#include <iostream>
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
void Event::addTicket(const int ID,const int row, const int seat, const std::string status, const std::string note) {
	this->hall.getList().push_back(Ticket(ID ,row, seat, status, note));
}