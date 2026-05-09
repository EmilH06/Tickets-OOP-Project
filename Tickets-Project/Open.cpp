#include <iostream>
#include <fstream>
#include <stdexcept>
void validInput(std::fstream& file) {
	if (!file.is_open()) {
		throw std::invalid_argument("Incorrect input for a filename!");
    }
}
class Open {
	std::fstream file;
public:
	Open(const std::string filename) {
		file.open(filename, std::ios::in);
		try {
			validInput(file);
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
	}
};