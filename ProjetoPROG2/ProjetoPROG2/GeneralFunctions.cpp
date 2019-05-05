#include <iostream>
#include <string>
#include <sstream>

#include "GeneralFunctions.h"

using namespace std;

void trimLeft(string &s)
{
	s.erase(0, s.find_first_not_of(" "));
}

void trimRight(string &s)
{
	s.erase(s.find_last_not_of(" ") + 1);
}

void trim(string &s)
{
	trimLeft(s);
	trimRight(s);
} 

bool VATConfirm(int VAT)
{
	int vDigits = 0;
	while (VAT != 0)
	{
		VAT /= 10;
		vDigits += 1;
	}
	if (vDigits == 9)
		return false;
	return true;
}

int slashCount(string reader)
{
	istringstream iS(reader);
	int pos, count = 0;
	
	while (true)
	{
		pos = reader.find('/');
		if (pos == -1)
			break;
		else
		{
			count++;
			reader.erase(pos, 1);
		}
	}
	return count;
}

bool adrConfirm(string &reader) // Rua Sem Nome / 100 / - / 4400-345 / Porto
{
	if (slashCount(reader) == 4)
	{
		istringstream iS(reader);
		string streamInfo;
		getline(iS, streamInfo, '/');
		if (streamInfo == "")
			return true;
		getline(iS, streamInfo, '/');
		trim(streamInfo);
		if (streamInfo.find_first_not_of("0123456789") != string::npos || streamInfo == "")
			return true;
		getline(iS, streamInfo, '/');
		trim(streamInfo);
		if (streamInfo.find_first_not_of("0123456789") != string::npos || streamInfo == "")
		{
			if(streamInfo != "-")
				return true;
		}
		getline(iS, streamInfo, '/');
		trim(streamInfo);
		if (streamInfo.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.^`*?!|#$%&/()=»«<>") != string::npos || streamInfo == "")
			return true;
		getline(iS, streamInfo, '/');
		trim(streamInfo);
		if (streamInfo.find_first_of("0123456789") != string::npos || streamInfo == "")
			return true;
		return false;
	}
	return true;
}

bool leapYear(int year)
{
	if (year % 4 == 0 && year % 100 != 0)
		return true;
	else if (year % 4 == 0 && year % 400 == 0)
		return true;
	return false;
}

int days(int year, int month)
{
	int d[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && leapYear(year))
		return 29;
	else
		return d[month - 1];
}