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
std::ostream& operator<<(std::ostream& out, const Event& information) {
	out << "<EVENT START>\n";
	out << "Name:" << information.getName()<<'\n';
	out << "Date:" << information.getDate() << '\n';
	out << "Hall:" << information.getHallName() << '\n';
	out << "<EVENT END>\n";
	return out;
}
Manager::Manager() {
	std::ifstream file("data/HallsInformation.txt", std::ios::in);
	if (!file.is_open()) {
		throw std::runtime_error("Access denied! File is in use or it can't be accessed!");
	}
	std::string buffer, hall_name;
	int rows, cols;
	while (true) {
		std::getline(file>>std::ws, hall_name, ':');
		if (file.eof() || file.fail()) {
			break;
		}
		file >> rows >> cols;
		avaiable_halls.push_back(Hall(hall_name,rows,cols));
		std::getline(file, buffer);
	}
	file.close();
};
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
	file.seekg(0, std::ios::beg);
	access = true;
	std::string category;
	std::string EventName, Date, HallName;
	struct TicketReader {
		int Ticket_row, Ticket_seat, Ticket_ID;
		std::string Ticket_status, Ticket_note;
	};
	std::vector<TicketReader> ticketList;
	auto hallByIdx = [&](std::string name) -> Hall& {
		for (size_t i = 0; i < avaiable_halls.size(); i++) {
			if (avaiable_halls[i].getName() == name) {
				return avaiable_halls[i];
			}
		}
		throw std::runtime_error("There isn't a hall with that name avaiable!");
	};
	while (true) {
		std::getline(file>>std::ws, category, ':');
		if (file.eof() || file.fail()) {
			break;
		}
		if (category == "<EVENT START>") {
			EventName.clear();
			Date.clear();
			HallName.clear();
			ticketList.clear();
			continue;
		}
		if (category == "<EVENT END>") {
			if (EventName.empty() || Date.empty() || HallName.empty()) {
				throw std::logic_error("Couldn't read information properly. Invalid argument!");
			}
			Event newEvent(EventName, Date, hallByIdx(HallName));
			info.push_back(newEvent);
			EventName.clear();
			Date.clear();
			HallName.clear();
			ticketList.clear();
			continue;
		}
		if (category == "Name") {
			std::getline(file, EventName);
		}
		if (category == "Date") {
			std::getline(file, Date);
		}
		if (category == "Hall") {
			std::getline(file, HallName);
		}
		if (category == "Tickets") {
			std::string skip;
			int position;
			while (true) {
				file >> std::ws;
				position = file.tellg();
				std::getline(file, skip);
				if (file.eof() || file.fail()) {
					break;
				}
				if (skip == "<EVENT END>") {
					break;
				}
				file.seekg(position);
				TicketReader t;
				file >> t.Ticket_ID >> t.Ticket_row >> t.Ticket_seat >> t.Ticket_status;
				std::getline(file, t.Ticket_note);
				ticketList.push_back(t);
			}
			if (EventName.empty() || Date.empty() || HallName.empty()) {
				throw std::logic_error("Couldn't read information properly. Invalid argument!");
			}
			Event newEvent(EventName, Date, hallByIdx(HallName));
			for (TicketReader x : ticketList) {
				newEvent.addTicket(x.Ticket_ID, x.Ticket_row, x.Ticket_seat, x.Ticket_status, x.Ticket_note);
			}
			info.push_back(newEvent);
			EventName.clear();
			Date.clear();
			HallName.clear();
			ticketList.clear();
		}
	}
	file.close();
	std::cout << "Successfully opened file " << filename << std::endl;
}
void Manager::file_close(const std::string& filename) {
	if (!access) {
		throw std::logic_error("You haven't open any file!");
	}
	file.close();
	info.clear();
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
	for (Event x : info) {
		file << x;
	}
	file.close();
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
	for (Event x : info) {
		newFile << x;
	}
	filename = newName;
	newFile.close();
	file.close();
	std::cout << "Successfully saved another " << filename << std::endl;
}
void Manager::help() const{
	std::cout << "The following commands are supported:\n" << "open <file>   - opens <file>\n" <<
		"close         - closes currently opened file\n" << "save          - saves the currently opened file\n" <<
		"saveas <file> - saves the currently opened file in <file>\n" << "help          - prints this information\n" <<
		"exit          - exits the program\n";
}
void Manager::file_exit() {
	access = false;
	info.clear();
	std::cout << "Exiting the program...";
}
void Manager::addevent() {
	if (!access) {
		throw std::logic_error("You haven't open any file!");
	}

	std::string name, date, hall_name;
	std::cin >> date;
	std::cin.ignore();
	std::getline(std::cin, name);
	std::getline(std::cin, hall_name);
	isValidHall(hall_name);
    isValidDate(date, hall_name);
	isValidEventName(name);
	auto hallByIdx = [&](std::string name) -> Hall& {
		for (size_t i = 0; i < avaiable_halls.size(); i++) {
			if (avaiable_halls[i].getName() == name) {
				return avaiable_halls[i];
			}
	}};
	info.push_back(Event(name,date,hallByIdx(hall_name)));
	std::cout << "Successfully added event:" << name<<std::endl;
}
void Manager::isValidEventName(const std::string name) const {
	if (name.empty()) {
		throw std::invalid_argument("Error: Name cannot be empty!");
	}
}
void Manager::isValidHall(const std::string hall) const {
	auto name_validator = [&]()->bool {for (Hall x : avaiable_halls) { if (x.getName() == hall) return true; }return false; };
	if (!name_validator()) {
		throw std::invalid_argument("There isn't avaiable hall with that name!");
	}
}
void Manager::isValidDate(const std::string date, const std::string hall_name) const {
	auto matchingDates = [&]()->bool {
		for (Event x: info){
			std::string other = x.getDate();
			if (hall_name==x.getHallName() &&date.substr(0, 4) == other.substr(0, 4) && date.substr(5, 2) == other.substr(5, 2) && date.substr(8, 2) == other.substr(8, 2)) {
				return true;
			}
		}
		return false;
	};
	if (date.size() != 10) {
		throw std::invalid_argument("Invalid date format. Input should have 10 symbols!");
	}
	if (date[4] != '-' || date[7] != '-') {
		throw std::invalid_argument("Invalid date format. Format should be: 'xxxx-xx-xx'!");
	}
	for (size_t i = 0; i < date.size(); i++) {
		if (i != 4 && i != 7) {
			if (date[i] < '0' || date[i]>'9') {
				throw std::invalid_argument("Invalid date format. The input should consist only of numbers and '-' as shown: 'YYYY-MM-DD'");
			}
		}
	}
	int year = std::stoi(date.substr(0, 4));
	int mouth = std::stoi(date.substr(5, 2));
	int day = std::stoi(date.substr(8, 2));
	auto validDay = [&]()->bool {
		switch (mouth) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: return (day >= 1 && day <= 31);
		case 2: if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			return (day >= 1 && day <= 29);
		}
			  else { return (day >= 1 && day <= 28); }
		case 4:
		case 6:
		case 9:
		case 11: return (day >= 1 && day <= 30);
		default: throw std::invalid_argument("Invalid date format. The mouth should be betweemn 1 and 12");
		}
		return false;
	};
	if (!validDay()) {
		throw std::invalid_argument("Invalid date format. This mouth doesn't have that many days!");
	}
	if (matchingDates()) {
		throw std::invalid_argument("Invalid date format. This date has already been reserved!");
	}
}