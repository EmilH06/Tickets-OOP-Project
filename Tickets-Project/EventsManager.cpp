#include "EventsManager.h"
#include "Ticket.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
struct BookingInfo {
	int row;
	int seat;
	std::string date;
	std::string name;
	std::string note = "";
};
void data_input(bool& access, BookingInfo& info) {
	if (!access) {
		throw std::logic_error("You haven't open any file!");
	}
	if (!(std::cin >> info.row >> info.seat >> info.date)) {
		throw std::invalid_argument("Invalid input format! Correct: book <row> <seat> <date> <name> <\"note\">");
	}
	if (info.row < 0 || info.seat < 0) {
		throw std::logic_error("The row and the seat can't be negative numbers");
	}
}
void validate_FileName(std::string& filename) {
	size_t size= filename.length();
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
std::ostream& operator<<(std::ostream& out, Event& information) {
	std::vector<Ticket> copy = information.getList();
	out << "<EVENT START>" << '\n';
	out << "Name:" << information.getName()<<'\n';
	out << "Date:" << information.getDate() << '\n';
	out << "Hall:" << information.getHallName() << '\n';
	out << "Tickets:"<<'\n';
	for (Ticket x : copy) {
		out <<x.getCode()<<' ' << x.getRow() << ' ' << x.getSeat() << ' ' << x.getStatus() << ' ' << x.getNote() << '\n';
	}
	out << "<EVENT END>"<<'\n';
	return out;
}
Manager::Manager(){
	std::ifstream file("data/HallsInformation.txt", std::ios::in);
	if (!file.is_open()) {
		throw std::runtime_error("Access denied! File is in use or it can't be accessed!");
	}
	std::string buffer, hall_name;
	int rows, cols;
	while (std::getline(file >> std::ws, hall_name, ':')) {
		if (file.eof() || file.fail()) {
			break;
		}
		file >> rows >> cols;
		this->avaiable_halls.push_back(Hall(hall_name,rows,cols));
		std::getline(file, buffer);
	}
	file.close();
}
void Manager::functionApply(std::string name, std::string date, const std::function<void(Event&)> func) {
	bool foundMatch = false;
	for (int i = 0; i < info.size(); i++) {
		if (name == info[i].getName() && date == info[i].getDate()) {
			foundMatch = true;
			func(info[i]);
			break;
		}
	}
	if (!foundMatch) {
		throw std::invalid_argument("There isn't an event registered to this name and date!");
	}
}
void Manager::file_open(std::string& filename) {
	if (access) {
		std::cin.ignore(1024, '\n');
		throw std::logic_error("Another file has already been opened. Close it before opening a new one!");
	}
	std::cin >> filename;
	validate_FileName(filename);
	file.clear();
	file.open("data/"+filename, std::ios::in | std::ios::out | std::ios::app);
	if (!file.is_open()) {
		throw std::runtime_error("Access denied! File is in use or it can't be accessed!");
	}
	file.seekg(0, std::ios::beg);
	access = true;
	std::string line;
	std::string EventName, Date, HallName;
	struct TicketReader {
		int Ticket_row; int Ticket_seat;
		std::string Ticket_status; std::string Ticket_note; std::string Ticket_code;
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
	while (std::getline(file>>std::ws,line)) {
		if (file.eof() || file.fail()) {
			break;
		}
		if (line == "<EVENT START>") {
			EventName.clear();
			Date.clear();
			HallName.clear();
			ticketList.clear();
			continue;
		}
		if (line == "<EVENT END>") {
				if (EventName.empty() || Date.empty() || HallName.empty()) {
					throw std::logic_error("Couldn't read information properly. Invalid argument!");
				}
				Event newEvent(EventName, Date, hallByIdx(HallName));
				for (const TicketReader& x : ticketList) {
					newEvent.addTicket(x.Ticket_code,x.Ticket_row, x.Ticket_seat, x.Ticket_status, x.Ticket_note);
				}
				this->info.push_back(newEvent);
			EventName.clear();
			Date.clear();
			HallName.clear();
			ticketList.clear();
			continue;
		}
		size_t place = line.find(':');
		std::string category = line.substr(0, place);
		std::string value = line.substr(place + 1);
		if (category == "Name") {
			EventName = value;
		}
		else if (category == "Date") {
			Date = value;
		}
		else if (category == "Hall") {
			HallName = value;
		}
		else if (category == "Tickets") {
			while (true) {
				if (file.eof()) {
					break;
				}
				int position = file.tellg();
				std::getline(file>>std::ws,line);
				if (line=="<EVENT END>") {
					file.seekg(position);
					break;
				}
				file.seekg(position);
				TicketReader t;
				if (file >>t.Ticket_code>>t.Ticket_row >> t.Ticket_seat >> t.Ticket_status) {
					std::getline(file, t.Ticket_note);
					if (!t.Ticket_note.empty() && t.Ticket_note[0] == ' ') {
						t.Ticket_note.erase(0, 1);
					}
					ticketList.push_back(t);
				}
				else {
					throw std::invalid_argument("Couldn't load the Ticket information!");
				}
			}
		}
	}
	file.clear();
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
	file.open("data/"+filename, std::ios::out | std::ios::in | std::ios::trunc);
	if (!file.is_open()) {
		throw std::runtime_error("Access denied! File is in use or it can't be accessed!");
	}
	for (Event& x : info) {
		file << x;
	}
	file.close();
	file.clear();
	file.open("data/"+filename, std::ios::in | std::ios::out | std::ios::app);
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
	for (Event& x : info) {
		newFile << x;
	}
	filename = newName;
	newFile.close();
	file.close();
	file.open("data/"+filename, std::ios::in | std::ios::out | std::ios::app);
	std::cout << "Successfully saved another " << filename << std::endl;
}
void Manager::help() const {
	std::cout << "The following commands are supported:\n"
		<< "open <file>                     - opens <file>\n"
		<< "close                           - closes currently opened file\n"
		<< "save                            - saves the currently opened file\n"
		<< "saveas <file>                   - saves the currently opened file in <file>\n"
		<< "help                            - prints this information\n"
		<< "exit                            - exits the program\n"
		<< "addevent <date> <hall> <name>   - adds a new performance\n"
		<< "freeseats <date> <name>         - prints available seats\n"
		<< "book <row> <seat> <date> <name> <note> - books a ticket\n"
		<< "unbook <row> <seat> <date> <name> - cancels the reservation\n"
		<< "buy <row> <seat> <date> <name>  - purchases a ticket\n"
		<< "bookings [<date>] [<name>]      - prints reserved tickets\n"
		<< "check <code>                    - prints ticket info\n"
		<< "report <from> <to> [<hall>]     - prints events in range\n"
		<< "mostviewed                      - prints ranking of performances\n"
		<< "attendence <from> <to>          - prints underperformers\n";
}
void Manager::file_exit() {
	access = false;
	info.clear();
	avaiable_halls.clear();
	std::cout << "Exiting the program...";
}
void Manager::addevent() {
	if (!access) {
		throw std::logic_error("You haven't open any file!");
	}
	std::string name, date, hall_word, hallNum;
		if (!(std::cin >> date >> hall_word >> hallNum)) {
			throw std::invalid_argument("Invalid input format! Correct: addevent <YYYY-MM-DD> <hall_name> <event_name>");
		}
		std::string hall_name = hall_word + ' ' + hallNum;
		std::cin >> std::ws;
		std::getline(std::cin, name);
		isValidHall(hall_name);
		isValidDate(date);
		isAvaiableDate(date, hall_name);
		isValidEventName(name);
		auto hallByIdx = [&](std::string name) -> Hall& {
			for (size_t i = 0; i < avaiable_halls.size(); i++) {
				if (avaiable_halls[i].getName() == name) {
					return avaiable_halls[i];
				}
			}
			throw std::runtime_error("There isn't a hall with that name avaiable!");
			};
		this->info.push_back(Event(name, date, hallByIdx(hall_name)));
		std::cout << "Successfully added event:" << name << std::endl;
}
void Manager::freeseats() {
	std::string name, date;
	if (!(std::cin >> date)) {
		throw std::invalid_argument("Invalid input format! Correct: freeseats <YYYY-MM-DD> <name>");
	}
	std::cin >> std::ws;
	std::getline(std::cin,name);
	isValidEventName(name);
	functionApply(name, date, [&](Event& e)->void {e.getFreeseats(); });
}
void Manager::book() {
	BookingInfo info;
	std::string line;
	data_input(this->access, info);
	std::cin >> std::ws;
	std::getline(std::cin, line);
	size_t firstApp = line.find('"');
	size_t secondApp = line.find('"', firstApp + 1);
	if (firstApp == std::string::npos || secondApp == std::string::npos) {
		throw std::invalid_argument("The note should be enclosed in quotes, if your note is empty write <\"\"> ");
	}
	info.name = line.substr(0, firstApp-1);
	info.note = line.substr(firstApp, secondApp);
	isValidEventName(info.name);
	bool foundMatch = false;
	functionApply(info.name,info.date,[&](Event& e)->void{ e.addTicket("none", info.row, info.seat, "RESERVED", info.note); });
	std::cout << "Successfully booked your seat!" << std::endl;
}
void Manager::unbook() {
	BookingInfo info;
	data_input(this->access,info);
	std::cin >> std::ws;
	std::getline(std::cin, info.name);
	isValidEventName(info.name);
	functionApply(info.name, info.date, [&](Event& e)->void {e.removeTicket(info.row, info.seat); });
	std::cout << "Successfully unbooked your seat!" << std::endl;
}
void Manager::buy() {
	BookingInfo info;
	data_input(this->access, info);
	std::cin >> std::ws;
	std::getline(std::cin, info.name);
	isValidEventName(info.name);
	functionApply(info.name, info.date, [&](Event& e)->void { e.purchaseTicket(info.name,info.date, info.row, info.seat, info.note); });
	std::cout << "Successfully purchased your seat!" << std::endl;
}
void Manager::bookings() {
	if (!access) {
		std::cin.ignore(1024, '\n');
		throw std::logic_error("You haven't open any file!");
	}
	std::string line;
	std::string name, date;
	std::cin >> std::ws;
	std::getline(std::cin, line);
	size_t spacePos = line.find(' ');
	if (spacePos != std::string::npos) {
		date = line.substr(0, spacePos);
		name = line.substr(spacePos + 1);
	}
	else if (!line.empty()) {
		if (line.find('-') != std::string::npos && line.length()==10) { date = line; }
		else { name = line; }
	}
	bool foundMatch = false;
	if (!name.empty() && !date.empty()) {
		functionApply(name, date, [&](Event& e)->void { e.getBookedSeats(); });
		return;
	}
	else if (name.empty() && !date.empty()) {
		std::cout << "Events on date " << date << ":\n";
		for (int i = 0; i < info.size(); i++) {
			if (date == info[i].getDate()) {
				foundMatch = true;
				std::cout << "Perormance: " << info[i].getName() << '\n';
				info[i].getBookedSeats();
			}
		}
	}
	else if(!name.empty() && date.empty() ){
		std::cout << "Events with name " << name << ":\n";
		for (int i = 0; i < info.size(); i++) {
			if (name == info[i].getName()) {
				foundMatch = true;
				std::cout << "Perormance: " << info[i].getName() <<" ("<<date<<")\n";
				info[i].getBookedSeats();
			}
		}
	}
	else if (name.empty() && date.empty()) {
		std::cout << "Events\n";
		for (int i = 0; i < info.size(); i++) {
				foundMatch = true;
				std::cout << "Perormance: " << info[i].getName() << " (" << info[i].getDate() << ")\n";
				info[i].getBookedSeats();
		}
	}
	if (!foundMatch) {
		throw std::invalid_argument("There isn't an event registered to this name or date!");
	}
}
void Manager::check() {
	if (!access) {
		std::cin.ignore(1024, '\n');
		throw std::logic_error("You haven't open any file!");
	}
	std::string code;
	if (!(std::cin >> code)) {
		throw std::invalid_argument("Invalid input format! Correct: check <code>");
	}
	for (Event e : info) {
		if (e.checkCode(code)) {
			return;
		}
	}
	throw std::logic_error("Invalid ticket code");
}
void Manager::report() {
	if (!access) {
		std::cin.ignore(1024, '\n');
		throw std::logic_error("You haven't open any file!");
	}
	std::string from, to, hallname;
	if (!(std::cin >> from>>to)) {
		throw std::invalid_argument("Invalid input format! Correct: report <from> <to> [<hall>]");
	}
	std::getline(std::cin, hallname);
	isValidDate(from);
	isValidDate(to);
	if (!hallname.empty()) {
		isValidHall(hallname);
		std::cout << "LIST OF EVENT FROM " << hallname << std::endl;;
		for (int i = 0; i < info.size(); i++) {
			if (hallname == info[i].getHallName()) {
				info[i].getReport(from,to);
			}
		}
	}
	else {
		std::cout << "LIST OF ALL EVENTS" << std::endl;
		for (int i = 0; i < info.size(); i++) {
				info[i].getReport(from, to);
		}
	}
}
void Manager::mostviewed() {
	if (!access) {
		throw std::logic_error("You haven't open any file!");
	}
	std::vector<Event> copy = this->info;
	std::cout << "Most viewd event is:\n";
	for (int i = 0; i < 3; i++) {
		std::cout << i + 1 << ".";
		size_t maxIdx = 0;
		for (size_t j = 0; j < copy.size(); j++) {
			if (copy[j].getList().size() > copy[maxIdx].getList().size()) {
				maxIdx = j;
			}
		}
		std::cout << copy[maxIdx].getName() << " - " << copy[maxIdx].getList().size() << " tickets sold\n";
		if (copy.empty()) {
			break;
		}
		copy.erase(copy.begin() + maxIdx);
	}
	std::cout << std::endl;
}
void Manager::attendence() {
	if (!access) {
		std::cin.ignore(1024, '\n');
		throw std::logic_error("You haven't open any file!");
	}
	std::string from, to;
	if (!(std::cin >> from >> to)) {
		throw std::invalid_argument("Invalid input format! Correct: report <from> <to> [<hall>]");
	}
	isValidDate(from);
	isValidDate(to);
	std::vector<int> IdxList;
	for (size_t i = 0; i < info.size(); i++) {
		if (info[i].getAttendence(from, to)) {
			IdxList.push_back(i);
		}
	}
	std::cout << "You can take down any of the underperformers by typing: <date> <name>. If not type \"No\" or leave it empty!\n";
	std::cout << "Your choice: ";
	std::string command;
	std::getline(std::cin >> std::ws, command);
	if (command == "No" || command.empty()) {
		return;
	}
	auto existInList = [&](std::string& name, std::string& date)->int {for (int index : IdxList) {
		if (info[index].getName() == name && info[index].getDate() == date) return index;} return -1; };
	size_t pos = command.find(' ');
	if (pos == std::string::npos) { throw std::invalid_argument("Invalid command!"); }
	std::string date = command.substr(0, pos);
	std::string name = command.substr(pos + 1);
	int validator = existInList(name, date);
	if (validator!=-1) {
		info.erase(info.begin() + validator);
		std::cout << "Successfully removed the event!";
		return;
	}
	throw std::invalid_argument("The name and date provided dont't exist withing the underperformers list!");
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
void Manager::isValidDate(const std::string date) const {
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
		} else { 
			return (day >= 1 && day <= 28); 
		}
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
}
void Manager::isAvaiableDate(const std::string date, const std::string hall_name) const {
	auto matchingDates = [&]()->bool {
		for (Event x : info) {
			std::string other = x.getDate();
			if (hall_name == x.getHallName() && date.substr(0, 4) == other.substr(0, 4) && date.substr(5, 2) == other.substr(5, 2) && date.substr(8, 2) == other.substr(8, 2)) {
				return true;
			}
		}
		return false;
		};
	if (matchingDates()) {
		throw std::invalid_argument("Invalid date format. This date has already been reserved!");
	}
}