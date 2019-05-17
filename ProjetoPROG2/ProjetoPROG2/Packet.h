#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Date.h"

using namespace std;

class Packet {
private:
	int id; // packet unique identifier
	vector<string> sites; // touristic sites to visit
	Date begin;  // begin date
	Date end;  // end date
	double pricePerPerson; // price per person
	unsigned maxPersons; // number of persons still available in the packet (updated whenever the packet is sold to a new client)
	unsigned currentPersons; // Current number of people that embrace the packet

public:
	// Constructors
	
	Packet(); // Default constructor
	Packet(vector<string> sites, Date begin, Date end, double pricePerPerson, unsigned maxPersons); // constructor for a new pack
	
	// GET methods

	int getId() const;
	string getSites() const; // Return sites in a string format
	vector<string> getSitesVector() const; // Return sites in a vector of strings
	Date getBeginDate() const;
	Date getEndDate() const;
	double getPricePerPerson() const;
	unsigned getMaxPersons() const; // get the maximum number of people that can buy the pack
	unsigned getCurrentPersons() const; // get the current number of people that have bought the pack

	// SET methods

	void setId(int id);  // to set negative if "deprecated"
	void setSites(vector<string> sites);
	void setBeginDate(Date begin);
	void setEndDate(Date end);
	void setPricePerPerson(double pricePerPerson);
	void setMaxPersons(unsigned maxPersons); // set the maximum number of people that can buy the pack
	void setCurrentPersons(unsigned takenTickets); // set the current number of people that have bought the pack

	// other methods
	bool sitesFormat(string &sitesStr); // returns "true" if the string "sitesStr" has a valid format of a pack's sites list
	friend ostream& operator<<(ostream& out, const Packet & packet); // overload operator << (display the formatted pack on a ostream)
};
