#include <sstream>
#include "Date.h"

Date::Date() {
}

Date::Date(string date) {

	istringstream Dat(date);
	string dayS, monthS, yearS;
	getline(Dat, yearS, '/');
	getline(Dat, monthS, '/');
	getline(Dat, dayS, '/');
	day = (unsigned short)stoi(dayS);
	month = (unsigned short)stoi(monthS);
	year = (unsigned short)stoi(yearS);
}


Date::Date(unsigned short day, unsigned short month, unsigned year) {

	// REQUIRES IMPLEMENTATION
}

/*********************************
 * GET Methods
 ********************************/
unsigned short Date::getDay() const {

	return day;

}


unsigned short Date::getMonth() const {

	return month;

}

unsigned Date::getYear() const {

	return year;

}

string Date::getDate() const
{
	return to_string(year) + "/" + to_string(month) + "/" + to_string(day);
}

/*********************************
 * SET Methods
 ********************************/

void Date::setDay(unsigned short day) {

	this->day = day;

}
void Date::setMonth(unsigned short month) {

	this->month = month;

}

void Date::setYear(unsigned year) {

	this->year = year;

}


/*********************************
 * Show Date
 ********************************/

 // disply a Date in a nice format
ostream& operator<<(ostream& out, const Date & date) {

	out << date.day << " / " << date.month << " / " << date.year;
	return out;
}
