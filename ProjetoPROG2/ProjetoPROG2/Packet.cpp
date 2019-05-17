#include <sstream>
#include <fstream>
#include <iomanip>
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

Packet::Packet() 
{
	id = 0;
	currentPersons = 0;
}
// metodos GET

int Packet::getId() const {

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

vector<string> Packet::getSitesVector() const
{
	return sites;
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

unsigned Packet::getCurrentPersons() const
{
	return currentPersons;
}

// metodos SET

void Packet::setId(int id) {

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

ostream& operator<<(ostream& out, const Packet & packet) {

	out << left << setw(45) << "ID: " << packet.id << endl
		<< left << setw(45) << "Sites visited: ";
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
		<< left << setw(45) << "Beggining date: " << packet.begin << endl
		<< left << setw(45) << "End date: " << packet.end << endl
		<< left << setw(45) << "Price per person: " << packet.pricePerPerson << endl
		<< left << setw(45) << "Number of initially available tickets: " << packet.maxPersons << endl
		<< left << setw(45) << "Bought tickets: " << packet.currentPersons << endl;
	return out;
}
