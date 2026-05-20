#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
class BasicCommand {
protected:
	bool access = false;
	bool file_saves = false;
public:
	virtual void file_open(const std::string&) = 0;
	virtual void file_close(const std::string&) = 0;
	virtual void file_save(const std::string&) = 0;
	virtual void file_saveas(std::string&) = 0;
	virtual void help() const = 0;
	virtual void file_exit() = 0;
	virtual ~BasicCommand() = default;
};