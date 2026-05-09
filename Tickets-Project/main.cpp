#include <iostream>
#include <vector>
#include <cstring>
int main() {
	std::string command;
	std::string filename;
	std::string copy;
	bool access = false;
	while (std::cout << "> " && std::cin >> command) {
		if (command == "open") {
			std::cin >> filename;
		}
	}
}