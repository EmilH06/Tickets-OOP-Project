#include "BasicCommands.h"
#include "EventsManager.h"
#include "InputParser.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <functional>
void error_catcher(std::function<void()> func) {
	try {
		func();
	}
	catch (std::invalid_argument& e) {
		std::cout << "Invalid input: " << e.what() << std::endl;
		std::cin.ignore(1024, '\n');
	}
	catch (std::logic_error& e) {
		std::cout << "Logic error: " << e.what() << std::endl;
		std::cin.ignore(1024, '\n');
	}
	catch (std::runtime_error& e) {
		std::cout << "System error: " << e.what() << std::endl;
		std::cin.ignore(1024, '\n');
	}
}
int main() {
	std::string command;
	std::string filename;
	InputParser parser;
	Manager mainTask;
	std::cout << "   TICKET ORGANIZER HAS BEEN OPENED        " << std::endl;
	std::cout << "   Input commands to manage your events.\n   " << std::endl;
	while (std::cout << "> " && std::cin>>command) {
	    if (command == "open") {
		    error_catcher([&]() {mainTask.file_open(filename); });
	    }
		else if (command == "close") {
			error_catcher([&]() {mainTask.file_close(filename); });
		}
		else if (command == "save") {
			error_catcher([&]() {mainTask.file_save(filename); });
		}
		else if (command == "saveas") {
			error_catcher([&]() {mainTask.file_saveas(filename); });
		}
		else if (command == "help") {
			mainTask.help();
		}
		else if (command == "exit") {
			mainTask.file_exit();
			break;
		}
		else if (command == "addevent") {
			error_catcher([&]() {mainTask.addevent(parser.getAddeventData()); });
		}
		else if (command == "freeseats") {
			error_catcher([&]() {mainTask.freeseats(parser.getFreeseatsData()); });
		}
		else if (command == "book") {
			error_catcher([&]() {mainTask.book(parser.getBookData()); });
		}
		else if (command == "unbook") {
			error_catcher([&]() {mainTask.unbook(parser.getUnbook_BoughtData()); });
		}
		else if (command == "buy") {
			error_catcher([&]() {mainTask.buy(parser.getUnbook_BoughtData()); });
		}
		else if (command == "bookings") {
			error_catcher([&]() {mainTask.bookings(parser.getBookingsData()); });
		}
		else if (command == "check") {
			error_catcher([&]() {mainTask.check(parser.getCheckData()); });
		}
		else if (command == "report") {
			error_catcher([&]() {mainTask.report(parser.getReportData()); });
		}
		else if (command == "mostviewed") {
			error_catcher([&]() {mainTask.mostviewed(); });
		}
		else if (command == "attendence") {
			error_catcher([&]() {mainTask.attendence(parser.getAttendenceData()); });
		}
		else{
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			std::cout << "Invalid command! Please use the allowed commands!" << std::endl;
		}
	}
}