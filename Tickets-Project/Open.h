#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
inline void validInput(std::fstream& file) {
	if (!file.is_open()) {
		throw std::invalid_argument("Incorrect input for a filename!");
    }
	else {
		std::cout << "Successfully opened file!";
	}
}
class Open {
	std::fstream file;
public:
	Open(const std::string filename) {
		file.open(filename, std::ios::in);
		try {
			validInput(file);
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
	}

	void replicate() {
		std::ofstream temp("temp.txt", std::ios::out);
		if (!temp) {
			std::cout << "Error";
		}
		char buffer[256];
		while (file.getline(buffer, 256)) {
			temp << buffer;
		}
	}
	~Open() {
		if (file.is_open()) { file.close(); }
	}
};