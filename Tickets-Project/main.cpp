#include "BasicCommands.h"
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
	BasicCommands task;
	while (std::cout << "> " && std::cin >> command) {
	    if (command == "open") {
				std::cin >> filename;
				error_catcher([&]() {task.file_open(filename); });
	    }
		else if (command == "close") {
			error_catcher([&]() {task.file_close(filename); });
		}
		else if (command == "save") {
			error_catcher([&]() {task.file_save(filename); });
		}
		else if (command == "saveas") {
			error_catcher([&]() {task.file_saveas(filename); });
		}
		else if (command == "exit") {
			std::cout << "Exiting the program...";
			break;
		}
	}
}