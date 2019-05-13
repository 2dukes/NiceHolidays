#pragma once
#include "Date.h"

void trim(std::string &s); // Removes extra spaces

void trimRight(std::string &s);

void trimLeft(std::string &s);

void decompose(std::string str, std::vector<std::string> &elements, char sep);

bool VATConfirm(int VAT);

int slashCount(std::string reader);

bool adrConfirm(std::string &reader);

bool leapYear(int year);

int days(int year, int month);
 
bool existingDate(string &dt);

bool endLaterThenBeg(string &endD, string &begD);

bool checkBetweenDates(std::string date1, std::string date2, Date date);

bool checkInt2(std::string s);

int checkInt(string sentence);

std::vector<int> vectorIntersec(std::vector<int> vector1, std::vector<int> vector2);