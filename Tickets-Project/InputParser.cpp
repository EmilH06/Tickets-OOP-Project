#include "InputParser.h"
#include <iostream>
#include <string>
#include <stdexcept>
AddeventInfo InputParser::getAddeventData() {
	AddeventInfo input;
	if (!(std::cin >> input.date >> input.hall_word >> input.hallNum)) {
		throw std::invalid_argument("Invalid input format! Correct: addevent <YYYY-MM-DD> <hall_name> <event_name>");
	}
	input.hall_name = input.hall_word + ' ' + input.hallNum;
	std::cin >> std::ws;
	std::getline(std::cin, input.name);
	return input;
}
BookingInfo InputParser::getFreeseatsData() {
	BookingInfo input;
	if (!(std::cin >> input. date)) {
		throw std::invalid_argument("Invalid input format! Correct: freeseats <YYYY-MM-DD> <name>");
	}
	std::cin >> std::ws;
	std::getline(std::cin, input.name);
	return input;
}
BookingInfo InputParser::getBookData() {
	BookingInfo input;
	if (!(std::cin >> input.row >> input.seat >> input.date)) {
		throw std::invalid_argument("Invalid input format! Correct: book <row> <seat> <date> <name> <\"note\">");
	}
	if (input.row < 0 || input.seat < 0) {
		throw std::logic_error("The row and the seat can't be negative numbers");
	}
	std::cin >> std::ws;
	std::getline(std::cin, input.line);
	size_t firstApp = input.line.find('"');
	size_t secondApp = input.line.find('"', firstApp + 1);
	if (firstApp == std::string::npos || secondApp == std::string::npos) {
		throw std::invalid_argument("The note should be enclosed in quotes, if your note is empty write <\"\"> ");
	}
	input.name = input.line.substr(0, firstApp - 1);
	input.note = input.line.substr(firstApp, secondApp);
	return input;
}
BookingInfo InputParser::getUnbook_BoughtData() {
	BookingInfo input;
	if (!(std::cin >> input.row >> input.seat >> input.date)) {
		throw std::invalid_argument("Invalid input format! Correct: book <row> <seat> <date> <name> <\"note\">");
	}
	if (input.row < 0 || input.seat < 0) {
		throw std::logic_error("The row and the seat can't be negative numbers");
	}
	std::cin >> std::ws;
	std::getline(std::cin, input.name);
	return input;
}
BookingInfo InputParser::getBookingsData() {
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
std::string InputParser::getCheckData() {
	std::string code;
	if (!(std::cin >> code)) {
		throw std::invalid_argument("Invalid input format! Correct: check <code>");
	}
	return code;
}
ReportInfo InputParser::getReportData() {
	ReportInfo input;
	if (!(std::cin >> input.from >> input.to)) {
		throw std::invalid_argument("Invalid input format! Correct: report <from> <to> [<hall>]");
	}
	std::getline(std::cin, input.hallname);
	return input;
}
ReportInfo InputParser::getAttendenceData() {
	ReportInfo input;
	if (!(std::cin >> input.from >> input.to)) {
		throw std::invalid_argument("Invalid input format! Correct: report <from> <to> [<hall>]");
	}
	return input;
}
