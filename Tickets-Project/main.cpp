#include "Open.h"
#include <iostream>
#include <vector>
#include <cstring>
int main() {
	std::string command;
	std::string filename;
	Open* file = nullptr;
	while (std::cout << "> " && std::cin >> command) {
		if (command == "open") {
			if (file != nullptr) {
				delete[] file;
			}
			file = new Open(filename);
			file->replicate();
		}
		else if (command == "exit") {
			if (file != nullptr) {
				delete file;
			}
			break;
		}
	}
	return 0;
}