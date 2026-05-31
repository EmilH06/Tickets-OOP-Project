#include "InputParser.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
template <typename T>
void extractOrthrow(std::stringstream& ss, T& value, const std::string& error) {
	if (!(ss >> value)) {
		throw std::invalid_argument(error);
	}
}
void validate_FileName(std::string& filename) {
	size_t size = filename.length();
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
	size_t nameIdx = filename.find("data/");
	if (nameIdx != std::string::npos) { filename.erase(0, 5); }
}
void InputParser::validateAcess(bool access) {
	if (!access) {
		std::cin.ignore(1024, '\n');
		throw std::logic_error("Another file has already been opened. Close it before opening a new one!");
	}
}
std::string InputParser::getFileName(std::string& filename,bool access) {
	if (access) {
		std::cin.ignore(1024, '\n');
		throw std::logic_error("Another file has already been opened. Close it before opening a new one!");
	}
	std::cin >> filename;
	validate_FileName(filename);
	return filename;
}
AddeventInfo InputParser::getAddeventData(bool access) {
	validateAcess(access);
	std::string line;
	if (!(std::getline(std::cin,line))) {
		throw std::invalid_argument("Invalid input format! Correct: addevent <YYYY-MM-DD> <hall_name> <event_name>");
	}
	std::stringstream ss(line);
	AddeventInfo input;
	extractOrthrow(ss, input.date, "Invalide date!");
	extractOrthrow(ss, input.hall_word, "Invalide hall!");
	extractOrthrow(ss, input.hallNum, "Invalide hall!");
	std::getline(ss >> std::ws, input.name);
	input.hall_name = input.hall_word + ' ' + input.hallNum;
	return input;
}
BookingInfo InputParser::getFreeseatsData(bool access) {
	validateAcess(access);
	BookingInfo input;
	std::string line;
	if (!(std::getline(std::cin, line))) {
		throw std::invalid_argument("Invalid input format! Correct: freeseats <date> <name>");
	}
	std::stringstream ss(line);
	extractOrthrow(ss, input.date, "Invalide date!");
	extractOrthrow(ss, input.name, "Invalide name!");
	return input;
}
BookingInfo InputParser::getBookData(bool access) {
	validateAcess(access);
	BookingInfo input;
	std::string line;
	if (!(std::getline(std::cin, line))) {
		throw std::invalid_argument("Invalid input format! Correct: freeseats <row> <seat> <date> <name> <note>");
	}
	std::stringstream ss(line);
	extractOrthrow(ss, input.row, "Invalide row!");
	extractOrthrow(ss, input.seat, "Invalide seat!");
	extractOrthrow(ss, input.date, "Invalide date!");
	std::getline(ss >> std::ws, input.line);
	size_t firstApp = input.line.find('"');
	size_t secondApp = input.line.find('"', firstApp + 1);
	if (firstApp == std::string::npos || secondApp == std::string::npos) {
		throw std::invalid_argument("The note should be enclosed in quotes, if your note is empty write <\"\"> ");
	}
	input.name = input.line.substr(0, firstApp - 1);
	input.note = input.line.substr(firstApp, secondApp);
	return input;
}
BookingInfo InputParser::getUnbook_BoughtData(bool access) {
	validateAcess(access);
	BookingInfo input;
	std::string line;
	if (!(std::getline(std::cin, line))) {
		throw std::invalid_argument("Invalid input format! Correct: freeseats <date> <name>");
	}
	std::stringstream ss(line);
	extractOrthrow(ss, input.row, "Invalide row!");
	extractOrthrow(ss, input.seat, "Invalide seat!");
	extractOrthrow(ss, input.date, "Invalide date!");
	std::getline(ss >> std::ws, input.name);
	return input;
}
BookingInfo InputParser::getBookingsData(bool access) {
	validateAcess(access);
	BookingInfo input;
	std::cin >> std::ws;
	std::getline(std::cin, input.line);
	size_t spacePos = input.line.find(' ');
	if (spacePos != std::string::npos) {
		input.date = input.line.substr(0, spacePos);
		input.name = input.line.substr(spacePos + 1);
	}
	else if (!input.line.empty()) {
		if (input.line.find('-') != std::string::npos && input.line.length() == 10) { input.date = input.line; }
		else { input.name = input.line; }
	}
	return input;
}
std::string InputParser::getCheckData(bool access) {
	validateAcess(access);
	std::string code;
	if (!(std::cin >> code)) {
		throw std::invalid_argument("Invalid input format! Correct: check <code>");
	}
	return code;
}
ReportInfo InputParser::getReportData(bool access) {
	if (!access) {
		std::cin.ignore(1024, '\n');
		throw std::logic_error("Another file has already been opened. Close it before opening a new one!");
	}
	ReportInfo input;
	std::string line;
	if (!(std::getline(std::cin, line))) {
		throw std::invalid_argument("Invalid input format! Correct: report <from> <to> [<hall>]");
	}
	std::stringstream ss(line);
	extractOrthrow(ss, input.from, "Invalide from-date!");
	extractOrthrow(ss, input.to, "Invalide to-date!");
	std::getline(ss >> std::ws, input.hallname);
	return input;
}
ReportInfo InputParser::getAttendenceData(bool access) {
	validateAcess(access);
	ReportInfo input;
	std::string line;
	if (!(std::getline(std::cin, line))) {
		throw std::invalid_argument("Invalid input format! Correct: report <from> <to>");
	}
	std::stringstream ss(line);
	extractOrthrow(ss, input.from, "Invalide from-date!");
	extractOrthrow(ss, input.to, "Invalide to-date!");
	return input;
}
