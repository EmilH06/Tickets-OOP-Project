#include "Event.h"
#include <iostream>
Event::Event(const std::string name, const std::string date, const Hall& hall_) : name(name), date(date), hall(hall_) {}
std::string Event::getDate() const {
	return date;
}
std::string Event::getName() const {
	return name;
}
std::string Event::getHallName() const {
	return hall.getName();
}
void Event::addTicket(const int ID,const int row, const int seat, const std::string status, const std::string note) {
	hall.getList().push_back(Ticket(ID ,row, seat, status, note));
}