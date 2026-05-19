#pragma once
#include "BasicCommands.h"
#include "Event.h"
#include <iostream>
#include <vector>
#include <string>
class Manager : public BasicCommand {
	std::fstream file;
	std::vector<Events> info;
	std::vector<std::string> avaiable_halls;
public:
	void file_open(const std::string& filename) override;
	void file_close(const std::string& filename) override;
	void file_save(const std::string& filename) override;
	void file_saveas(std::string& filename) override;
	void help() const override;
	void file_exit() override;
	~Manager() {
		if (!file.is_open()) {
			file.close();
		}
	}
};