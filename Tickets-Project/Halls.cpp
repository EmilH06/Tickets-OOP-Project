#include "Halls.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
	Hall::Hall(const std::string name_) : name(name_) {
	std::ifstream file("data/HallsInformation.txt", std::ios::in);
	if (!file.is_open()) {
			throw std::runtime_error("Access denied! File is in use or it can't be accessed!");
	}
	std::string buffer,hall_name;
	while (true) {
		std::getline(file>>std::ws, hall_name, ':');
		if (file.eof() || file.fail()) {
			break;
		}
		if (hall_name == name) {
			file >> rows >> cols;
			break;
		}
		std::getline(file, buffer);
	}
	file.close();
	seats.resize(rows, std::vector<int>(cols,0));
	}
	std::string Hall::getName() const {
		return name;
	}