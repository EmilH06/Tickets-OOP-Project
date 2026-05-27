#include "BasicCommands.h"
#include "EventsManager.h"
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
	}
	catch (std::logic_error& e) {
		std::cout << "Logic error: " << e.what() << std::endl;
	}
	catch (std::runtime_error& e) {
		std::cout << "System error: " << e.what() << std::endl;
	}
}
int main() {
	std::string command;
	std::string filename;
	Manager* mainTask = new Manager();
	while (std::cout << "> " && std::cin >> command) {
	    if (command == "open") {
		    error_catcher([&]() {mainTask->file_open(filename); });
	    }
		else if (command == "close") {
			error_catcher([&]() {mainTask->file_close(filename); });
		}
		else if (command == "save") {
			error_catcher([&]() {mainTask->file_save(filename); });
		}
		else if (command == "saveas") {
			error_catcher([&]() {mainTask->file_saveas(filename); });
		}
		else if (command == "help") {
			mainTask->help();
		}
		else if (command == "exit") {
			mainTask->file_exit();
			break;
		}
		else if (command == "addevent") {
			error_catcher([&]() {mainTask->addevent(); });
		}
		else if (command == "freeseats") {
			error_catcher([&]() {mainTask->freeseats(); });
		}
		else if (command == "book") {
			error_catcher([&]() {mainTask->book(); });
		}
		else if (command == "unbook") {
			error_catcher([&]() {mainTask->unbook(); });
		}
		else if (command == "buy") {
			error_catcher([&]() {mainTask->buy(); });
		}
		else if (command == "bookings") {
			error_catcher([&]() {mainTask->bookings(); });
		}
		else if (command == "check") {
			error_catcher([&]() {mainTask->check(); });
		}
		else if (command == "report") {
			error_catcher([&]() {mainTask->report(); });
		}
		else{
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			std::cout << "Invalid command! Please use the allowed commands!" << std::endl;
		}
	}
	delete mainTask;
}