#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Packet.h"
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
	int count = 0;
	size_t pos;
	
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

bool adrConfirm(string &reader) 
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

bool existingDate(string &dt)
{
	istringstream iS(dt);
	int year, month, day, maxDays;
	char delimiter; // Slash
	iS >> year;
	iS >> delimiter;
	if (delimiter != '/')
		return true;
	iS >> month;
	iS >> delimiter;
	if (delimiter != '/')
		return true;
	iS >> day;
	if (year >= 0 && (month >= 1 && month <= 12))
	{
		maxDays = days(year, month);
		if (day >= 1 && day <= maxDays)
			return false;
	}
	return true;
}

bool endLaterThenBeg(string &endD, string &begD)
{
	istringstream iS(endD);
	int endYear, endMonth, endDay;
	char delimiter; // Slash
	iS >> endYear;
	iS >> delimiter;
	iS >> endMonth;
	iS >> delimiter;
	iS >> endDay;

	iS.clear();
	iS.str(begD);
	int begYear, begMonth, begDay;
	iS >> begYear;
	iS >> delimiter;
	iS >> begMonth;
	iS >> delimiter;
	iS >> begDay;

	if (endYear < begYear)
		return true;
	else if (endMonth < begMonth && endMonth == begYear)
		return true;
	else if (endDay <= begDay && endMonth == begMonth && endYear == begYear)
		return true;
	return false;
}

bool checkBetweenDates(string date1, string date2, Date date)
{
	int date1day, date1month, date1year, date2day, date2month, date2year;
	istringstream iSdate1(date1), iSdate2(date2);
	char s;
	iSdate1 >> date1year >> s >> date1month >> s >>date1day;
	iSdate2 >> date2year >> s >> date2month >> s >> date2day;
	int entryDate = (date.getYear() * 10000) + (date.getMonth() * 100) + date.getDay();
	int startDate = (date1year * 10000) + (date1month * 100) + date1day;
	int endDate = (date2year * 10000) + (date2month * 100) + date2year;

	if (entryDate >= startDate && entryDate <= endDate)
		return true;
	else
		return false;
}

bool checkInt2(string s)
{
	bool confirm = true;
	for (const auto &c : s)
	{
		if (!isdigit(c))
		{
			confirm = false;
			break;
		}
	}
	return confirm;
} 

int checkInt(string sentence)
{
	string n;
	while (true)
	{ 
		cout << sentence;
		cin >> n;
		if (cin.eof())
			return -1;
		if (checkInt2(n))
			return stoi(n);
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, try again.\n";
		}
	}
}

vector<int> vectorIntersec(vector<int> &vector1, vector<int> &vector2)
{
	vector<int> finalVector;
	for (size_t i = 0; i < vector1.size(); i++)
	{
		for (size_t j = 0; j < vector2.size(); j++)
		{
			if (vector1.at(i) == vector2.at(j))
			{
				if (find(finalVector.begin(), finalVector.end(), vector1.at(i)) != finalVector.end())
					continue;
				else
					finalVector.push_back(vector1.at(i));
			}
		}
	}
	return finalVector;
}

vector<string> sitesNormalization(string &sitesStr)
{
	istringstream iS(sitesStr);
	vector<string> tSites;
	string mainPlace;
	getline(iS, mainPlace, '-');
	trim(mainPlace);
	tSites.push_back(mainPlace);
	if (iS.eof())
		return tSites;
	else
	{
		while (getline(iS, mainPlace, ','))
		{
			trim(mainPlace);
			if (mainPlace != "" && mainPlace.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") == string::npos)
				tSites.push_back(mainPlace);
		}	
	}
	return tSites;
}