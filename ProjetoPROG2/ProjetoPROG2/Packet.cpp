#include <sstream>
#include "Packet.h"
#include "GeneralFunctions.h"

Packet::Packet(vector<string> sites, Date inicio, Date fim, double precoPessoa, unsigned maxPessoas){

  // REQUIRES IMPLEMENTATION
}

  // metodos GET

unsigned Packet::getId() const{

	return id;
}

vector<string> Packet::getSites() const{

	return sites;
}

Date Packet::getBeginDate() const{

	return begin;
}

Date Packet::getEndDate() const{

	return end;
}

double Packet::getPricePerPerson() const{

	return pricePerPerson;
}

unsigned Packet::getMaxPersons() const{

	return maxPersons;
}

  // metodos SET

void Packet::setId(unsigned id){

	this->id = id;
}

void Packet::setSites(vector<string> sites){

	this->sites = sites;
}

void Packet::setBeginDate(Date begin){

	this->begin = begin;
}

void Packet::setEndDate(Date end){

	this->end = end;
}

void Packet::setPricePerPerson(double pricePerPerson){

	this->pricePerPerson = pricePerPerson;
}

void Packet::setMaxPersons(unsigned maxPersons){

	this->maxPersons = maxPersons;
}


/*********************************
 * Show Packet information
 ********************************/  

bool Packet::sitesFormat(string sitesStr)
{
	istringstream iS(sitesStr);
	string mainPlace;
	getline(iS, mainPlace, '-'); 
	if (iS.eof())
		return false;
	else
	{
		while (getline(iS, mainPlace, ','))
		{
			if (mainPlace == "")
				return true;
		}
		if (mainPlace.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos)
			return true;
	}
	return false;
}

vector<string> Packet::sitesNormalization(string sitesStr)
{
	istringstream iS(sitesStr);
	vector<string> tSites;
	string mainPlace;
	getline(iS, mainPlace, '-');
	if (iS.eof())
	{
		tSites.push_back(mainPlace);
		return tSites;
	}
	else
	{
		while (getline(iS, mainPlace, ','))
		{
			if (mainPlace != "")
				tSites.push_back(mainPlace);
		}
		if (mainPlace.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") == string::npos)
			tSites.push_back(mainPlace);
	}
	return tSites;
}

bool existingDate(string dt)
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

bool endLaterThenBeg(string endD, string begD)
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

Packet Packet::packetCreation(string explorer)
{
	string reader, begD;
	double price;
	int tId, tMax;
	bool flag;

	system("cls");
	cout << explorer << endl << endl;
	// ofstream out_stream("packs.txt", std::ios_base::app);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "-> CTRL+Z to leave..." << endl << endl;
	cout << "Pack ID: ";
	// while (!(cin >> id) || !verifyIDExistence(to_string(q)) || id < 0) -> TO DO verifyIDExistence Compare with last inserted ID which will be a static variable in agency
	while ((!(cin >> tId) || tId < 0) && !cin.eof())
	{
		// cout << !verifyIDExistence(to_string(q)) << endl;
		cerr << "Invalid Option or existing ID! Please enter a valid input." << endl;
		cout << endl << "Pack ID: ";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	if (cin.eof())
		return;
	// out_stream << q << "\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Places to visit: "; getline(cin, reader); // Places format -> Porto - Porto, Gaia, Arcozelo | OR | Madeira (only)
	while ((reader.empty() || sitesFormat(reader)) && !cin.eof()) // Overload sitesFormat
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Places to visit: "; getline(cin, reader);
	}
	if (cin.eof())
		return;
	trim(reader);
	// out_stream << reader + "\n";

	cout << "Beginning date (Year / Month / Day): "; getline(cin, reader);
	while ((reader.empty() || existingDate(reader)) && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Beginning date (Year / Month / Day): "; getline(cin, reader);
	}
	if (cin.eof())
		return;
	trim(reader);
	begD = reader;
	// out_stream << reader + "\n";

	cout << "End date (Year / Month / Day): "; getline(cin, reader);
	while ((reader.empty() || existingDate(reader) || endLaterThenBeg(reader, begD)) && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "End date (Year / Month / Day): "; getline(cin, reader);
	}
	if (cin.eof())
		return;
	trim(reader);
	// out_stream << reader + "\n";

	cout << "Price per person: ";
	while (!(cin >> price) && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Price per person: ";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	if (cin.eof())
		return;
	// out_stream << rd << "\n";

	cout << "Max Lotation: ";
	while (!(cin >> tMax) && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Max Lotation: ";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	if (cin.eof())
		return;
	/*out_stream << q << "\n";
	out_stream << q << "\n";
	out_stream << "::::::::::\n";
	out_stream.close();*/

	cout << endl << "Your data was successfully inserted!" << endl << endl;
	system("pause");
}

// shows a packet content 
ostream& operator<<(ostream& out, const Packet & packet){

	out << packet.id << endl;
		for (size_t i = 0; i < packet.sites.size(); i++)
		{
			if (i == 0)
				out << packet.sites.at(0);
			else
			{
				if (i == 1)
					out << " - " + packet.sites.at(1);
				else
					out << ", " + packet.sites.at(i);
			}
		}
	out	<< endl
		<< packet.begin << endl
		<< packet.end << endl
		<< packet.pricePerPerson << endl
		<< packet.maxPersons << endl;
	return out;
}
