#pragma once
#include "BasicCommands.h"
#include "Ticket.h"
#include "Halls.h"
#include "Event.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
class Manager : public BasicCommand {
	std::fstream file;
	std::vector<Event> info;
    std::vector<Hall> avaiable_halls;
public:
	Manager();
	void file_open(const std::string&) override;
	void file_close(const std::string&) override;
	void file_save(const std::string&) override;
	void file_saveas(std::string&) override;
	void help() const override;
	void file_exit() override;
	void addevent() ;
	void isValidDate (const std::string, const std::string) const;
	void isValidHall(const std::string) const;
	void isValidEventName(const std::string) const;
	~Manager() {
		if (!file.is_open()) {
			file.close();
		}
	}
};