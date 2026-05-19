#include "EventsManager.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

void validate_FileName(const std::string& filename) {
	int size = filename.length();
	if (size < 5) {
		throw std::invalid_argument("File is too short!");
	}
	if (filename[size - 1] != 't' || filename[size - 2] != 'x' || filename[size - 3] != 't' || filename[size - 4] != '.') {
		throw std::invalid_argument("Invalid format! File supports only .txt format type!");
	}
	for (char c : filename) {
		if (c == '*' || c == '?' || c == '<' || c == '>' || c == '|') {
			throw std::invalid_argument("Filename contains forbidden characters!");
		}
	}
}
void Manager::file_open(const std::string& filename) {
	validate_FileName(filename);
	if (file.is_open()) {
		throw std::logic_error("Another file has already been opend. Close it before opening a new one!");
	}
	file.clear();
	file.open(filename, std::ios::in | std::ios::out | std::ios::app);
	if (!file.is_open()) {
		throw std::runtime_error("Access denied! File is in use or it can't be accessed!");
	}
	access = true;
	if (!file_saves) {
		std::cout << "Successfully opened file " << filename << std::endl;
	}
	else {
		std::cout << "Successfully saved another file " << filename << std::endl;
		file_saves = false;
	}
}
void Manager::file_close(const std::string& filename) {
	if (!access) {
		throw std::logic_error("You haven't open any file!");
	}
	file.close();
	access = false;
	std::cout << "Successfully closed document " << filename << std::endl;
}
void Manager::file_save(const std::string& filename) {
	if (!access) {
		throw std::logic_error("You haven't open any file!");
	}
	file.close();
	file.open(filename, std::ios::out | std::ios::in | std::ios::trunc);
	if (!file.is_open()) {
		throw std::runtime_error("Access denied! File is in use or it can't be accessed!");
	}

	std::cout << "Successfully saved file " << filename << std::endl;
}
void Manager::file_saveas(std::string& filename) {
	if (!access) {
		throw std::logic_error("You haven't open any file!");
	}
	std::string newName;
	std::cin >> newName;
	validate_FileName(newName);
	std::ofstream newFile(newName, std::ios::out | std::ios::trunc);
	if (!newFile.is_open()) {
		throw std::runtime_error("Incorrect location input or you're trying to access prohibited area!");
	}

	char buffer[256];
	while (file.getline(buffer, 256)) {
		newFile << buffer << '\n';
	}
	filename = newName;
	file_saves = true;
	newFile.close();
	file.close();
	file_open(filename);
}
void Manager::help() const{
	std::cout << "The following commands are supported:\n" << "open <file>   - opens <file>\n" <<
		"close         - closes currently opened file\n" << "save          - saves the currently opened file\n" <<
		"saveas <file> - saves the currently opened file in <file>\n" << "help          - prints this information\n" <<
		"exit          - exits the program\n";
}
void Manager::file_exit() {
	std::remove("temp.txt");
	access = false;
	std::cout << "Exiting the program...";
}