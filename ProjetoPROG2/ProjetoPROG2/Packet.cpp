#include <sstream>
#include <fstream>
#include "Packet.h"
#include "GeneralFunctions.h"

Packet::Packet(vector<string> sites, Date inicio, Date fim, double precoPessoa, unsigned maxPessoas)
{
	// Id will be incremented
	this->sites = sites;
	begin = inicio;
	end = fim;
	pricePerPerson = precoPessoa;
	maxPersons = maxPessoas;
	currentPersons = 0;
}

Packet::Packet() // Irregular packet
{
	id = 0;
	currentPersons = 0;
}
// metodos GET

unsigned Packet::getId() const {

	return id;
}

string Packet::getSites() const {

	string places;
	vector<string>::const_iterator sPtr;
	if (sites.size() == 1)
	{
		places = sites.at(0);
		return places;
	}
	else
		places = sites.at(0) + " - ";
	for (sPtr = sites.begin() + 1; sPtr != sites.end(); sPtr++)
	{
		places += *sPtr;
		if (sPtr + 1 != sites.end())
			places += ", ";
	}
	return places;
}

Date Packet::getBeginDate() const {

	return begin;
}

Date Packet::getEndDate() const {

	return end;
}

double Packet::getPricePerPerson() const {

	return pricePerPerson;
}

unsigned Packet::getMaxPersons() const {

	return maxPersons;
}

// metodos SET

void Packet::setId(unsigned id) {

	this->id = id;
}

void Packet::setSites(vector<string> sites) {

	this->sites = sites;
}

void Packet::setBeginDate(Date begin) {

	this->begin = begin;
}

void Packet::setEndDate(Date end) {

	this->end = end;
}

void Packet::setPricePerPerson(double pricePerPerson) {

	this->pricePerPerson = pricePerPerson;
}

void Packet::setMaxPersons(unsigned maxPersons) {

	this->maxPersons = maxPersons;
}

void Packet::setCurrentPersons(unsigned takenTickets)
{
	this->currentPersons = takenTickets;
}


/*********************************
 * Show Packet information
 ********************************/

bool Packet::sitesFormat(string &sitesStr)
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

vector<string> Packet::sitesNormalization(string &sitesStr)
{
	istringstream iS(sitesStr);
	vector<string> tSites;
	string mainPlace;
	getline(iS, mainPlace, '-');
	trim(mainPlace);
	tSites.push_back(mainPlace);
	// cout << mainPlace << endl;
	if (iS.eof())
		return tSites;
	else
	{
		while (getline(iS, mainPlace, ','))
		{
			trim(mainPlace);
			// cout << mainPlace << endl;
			if (mainPlace != "" && mainPlace.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") == string::npos)
				tSites.push_back(mainPlace);
		}	
	}
	// system("pause");
	return tSites;
}

bool Packet::existingDate(string &dt)
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

bool Packet::endLaterThenBeg(string &endD, string &begD)
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

void Packet::packetCreation(string &explorer)
{
	string reader, begD, endD, places;
	double price;
	int tMax;
	bool flag;

	system("cls");
	cout << explorer << endl << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "-> CTRL+Z to leave..." << endl << endl;

	cout << "Places to visit: "; getline(cin, places); // Places format -> Porto - Porto, Gaia, Arcozelo | OR | Madeira (only)

	while ((places.empty() || sitesFormat(places)) && !cin.eof()) // Overload sitesFormat
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Places to visit: "; getline(cin, places);

	}
	if (cin.eof())
		return;
	trim(places);
	sites = sitesNormalization(places);

	cout << "Beginning date (Year / Month / Day): "; getline(cin, begD);
	while ((begD.empty() || existingDate(begD)) && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Beginning date (Year / Month / Day): "; getline(cin, begD);
	}
	if (cin.eof())
		return;
	trim(begD);
	begin = Date(begD);

	cout << "End date (Year / Month / Day): "; getline(cin, endD);
	while ((endD.empty() || existingDate(endD) || endLaterThenBeg(endD, begD)) && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "End date (Year / Month / Day): "; getline(cin, endD);
	}
	if (cin.eof())
		return;
	trim(endD);
	end = Date(endD);

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
	pricePerPerson = price;

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
	maxPersons = tMax;

	// Construction PACKET
	// Date TemporaryBegin(begD), TemporaryEnd(endD);
	// NewPacket = Packet(sitesNormalization(places), TemporaryBegin, TemporaryEnd, price, tMax);
}

// shows a packet content 
ostream& operator<<(ostream& out, const Packet & packet) {

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
	out << endl
		<< packet.begin << endl
		<< packet.end << endl
		<< packet.pricePerPerson << endl
		<< packet.maxPersons << endl;
	return out;
}
