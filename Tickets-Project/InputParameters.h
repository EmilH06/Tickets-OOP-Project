#pragma once
#include <string>
#include <stdexcept>
struct AddeventInfo {
	std::string name; 
	std::string date; 
	std::string hall_name;
	std::string hall_word;
	std::string hallNum;
	void validate();
};
struct BookingInfo {
	int row = 0;
	int seat = 0;
	std::string date;
	std::string name;
	std::string note;
	std::string line;
	void validate();
};
struct ReportInfo {
	std::string from;
	std::string to;
	std::string hallname;
	std::string hall_word;
	std::string hallNum;
	std::string command;
	void validate();
};
void isValidDate(const std::string);