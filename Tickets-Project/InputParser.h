#pragma once
#include "InputParameters.h"
class InputParser {
public:
	void validateAcess(bool);
	std::string getFileName(std::string&, bool);
	AddeventInfo getAddeventData(bool);
	BookingInfo getFreeseatsData(bool);
	BookingInfo getBookData(bool);
	BookingInfo getUnbook_BoughtData(bool);
	BookingInfo getBookingsData(bool);
	std::string getCheckData(bool);
	ReportInfo getReportData(bool);
	ReportInfo getAttendenceData(bool);
};