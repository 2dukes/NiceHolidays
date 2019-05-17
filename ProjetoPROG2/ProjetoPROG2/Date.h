#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"

using namespace std;

class Date {
private:
	unsigned short day;
	unsigned short month;
	unsigned year;

public:
	// Constructors

	Date(); // Default constructor
	Date(string date); // constructor from a string date
	Date(unsigned short day, unsigned short month, unsigned year); // constructor from the separate elements of the date

	// GET methods
	unsigned short getDay() const;
	unsigned short getMonth() const;
	unsigned getYear() const;
	string getDate() const; // get the date on the form of a string (year/month/day)

	// SET methods

	void setDay(unsigned short day);
	void setMonth(unsigned short month);
	void setYear(unsigned year);

	// other methods

	friend ostream& operator<<(ostream& out, const Date & date); // overload of operator << (display the formatted date on a ostream)

};
