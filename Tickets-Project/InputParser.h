#pragma once
#include "InputParameters.h"
class InputParser {
public:
	std::string getFileName(std::string&);
	AddeventInfo getAddeventData();
	BookingInfo getFreeseatsData();
	BookingInfo getBookData();
	BookingInfo getUnbook_BoughtData();
	BookingInfo getBookingsData();
	std::string getCheckData();
	ReportInfo getReportData();
	ReportInfo getAttendenceData();
};