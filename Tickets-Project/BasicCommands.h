#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
class BasicCommands {
	std::fstream file;
public:
	void file_open(std::string filename) {};
	void file_close() {};
	void file_save() {};
	void file_saveas() {};
	void help() {};
	void exit() {};
};
