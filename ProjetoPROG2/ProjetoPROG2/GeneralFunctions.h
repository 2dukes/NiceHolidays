#pragma once


void trim(std::string &s); // Removes extra spaces

void trimRight(std::string &s);

void trimLeft(std::string &s);

void decompose(std::string str, std::vector<std::string> &elements, char sep);

bool VATConfirm(int VAT);

int slashCount(std::string reader);

bool adrConfirm(std::string &reader);

bool leapYear(int year);

int days(int year, int month);
