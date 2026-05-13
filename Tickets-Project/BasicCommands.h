#pragma once
#include <iostream>
#include <fstream>

class BasicCommands {
	std::fstream file;
	bool access = false;
	bool file_saves = false;
public:
	void file_open(const std::string& filename);
	void file_close(const std::string& filename);
	void file_save(const std::string& filename);
	void file_saveas(std::string& filename);
	void help();
	void file_exit();
	~BasicCommands() {
		if (!file.is_open()) {
			file.close();
		}
	}
};