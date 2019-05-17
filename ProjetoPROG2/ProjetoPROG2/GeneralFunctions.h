#pragma once
#include "Date.h"

void trim(std::string &s); // Removes extra spaces from the begining and end of a string

void trimRight(std::string &s); // removes extra spaces from the end of a string

void trimLeft(std::string &s); // removes extra spaces from the beginning of a string

bool VATConfirm(int VAT); // returns "true" if the argument "VAT" is a valid VAT number

int slashCount(std::string reader); // returns the number of chars '/' there is inside a string

bool adrConfirm(std::string &reader); // returns "true" if the string "reader" is a valid address. For example: "Rua Sem Nome / 100 / - / 4400-345 / Porto"

bool leapYear(int year); // returns "true" if the argument "year" is a leap year

int days(int year, int month); // returns the number of days in a month of a given year
 
bool existingDate(string &dt); // returns "true" if a string in the form of a date (year/month/day) is a valid date

bool endLaterThenBeg(string &endD, string &begD); // returns "true" if the string "begD" is a date later then the date on the "endD" string

bool checkBetweenDates(std::string date1, std::string date2, Date date); // returns "true" if the object "date" is a date between "date1" and "date2"

bool checkInt2(std::string s); // returns "true" if a string "sentence" can be converted to an integer

int checkInt(string sentence); // asks for an integer input until the user gives a valid integer and then returns it

std::vector<int> vectorIntersec(std::vector<int> &vector1, std::vector<int> &vector2); // returns the intersection of two given vectors of integers

std::vector<std::string> sitesNormalization(std::string &sitesStr); // decomposes the sites string and returns a vector of strings containing the sites