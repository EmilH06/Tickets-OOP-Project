#include "InputParameters.h"
#include <string>
#include <stdexcept>
#include <iostream>
void AddeventInfo::validate() {
	if (name.empty()) {
		throw std::invalid_argument("Error: Name cannot be empty!");
	}
	isValidDate(date);
}
void BookingInfo :: validate() {
	if (name.empty()) {
		throw std::invalid_argument("Error: Name cannot be empty!");
	}
	if (row <= 0 || seat <= 0) {
		throw std::logic_error("The row and the seat can't be negative numbers or 0");
	}
	isValidDate(date);

}
void ReportInfo::validate() {
	isValidDate(from);
	isValidDate(to);
}
void isValidDate(const std::string date) {
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
			  else {
			return (day >= 1 && day <= 28);
		}
		case 4:
		case 6:
		case 9:
		case 11: return (day >= 1 && day <= 30);
		default: throw std::invalid_argument("Invalid date format. The mounth should be betweemn 1 and 12");
		}
		return false;
		};
	if (!validDay()) {
		throw std::invalid_argument("Invalid date format. This mounth doesn't have that many days!");
	}
}