#pragma once
#include "InputParameters.h"
#include "BasicCommands.h"
#include "Ticket.h"
#include "Halls.h"
#include "Event.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
class Manager : public BasicCommand {
	std::fstream file;
	std::vector<Event> info;
    std::vector<Hall> avaiable_halls;
public:
	Manager();
	void functionApply(std::string name, std::string date, const std::function<void(Event&)>);
	void file_open(std::string&) override;
	void file_close(const std::string&) override;
	void file_save(const std::string&) override;
	void file_saveas(std::string&,std::string) override;
	void help() const override;
	void file_exit() override;
	void addevent(AddeventInfo) ;
	void freeseats(BookingInfo);
	void book(BookingInfo);
	void unbook(BookingInfo);
	void buy(BookingInfo);
	void bookings(BookingInfo);
	void check(std::string);
	void report(ReportInfo);
	void mostviewed();
	void attendence(ReportInfo);
	void isValidDate (const std::string) const;
	void isAvaiableDate(const std::string, const std::string) const;
	void isValidHall(const std::string) const;
	void isValidEventName(const std::string) const;
	~Manager() {
		if (file.is_open()) {
			file.close();
		}
	}
};