#include <sstream>
#include "Address.h"


Address::Address(string adr) 
{
	istringstream iS(adr);
	string adrInfo;
	int auxiliar;
    // Rua Sem Nome / 100 / - / 4400-345 / Porto
	// Suppose that file format is alright
	getline(iS, street, '/'); // Street
	getline(iS, adrInfo, '/');
	auxiliar = stoi(adrInfo);
	doorNumber = static_cast<unsigned short> (auxiliar); // doorNumber
	getline(iS, floor, '/');  // floor
	getline(iS, postalCode, '/'); // postalCode
	getline(iS, location); // location
}

Address::Address(string street, unsigned short doorNumber, string floor, string postalCode, string location) {

	// REQUIRES IMPLEMENTATION
}

// metodos GET


string Address::getStreet() const {

	return street;
}

unsigned short Address::getDoorNumber() const {

	return doorNumber;
}

string Address::getFloor() const {

	return floor;
}

string Address::getPostalCode() const {

	return postalCode;
}

string Address::getLocation() const {

	return location;
}


// metodos SET

void Address::setStreet(string street) {

	this->street = street;
}

void Address::setDoorNumber(unsigned short doorNumber) {

	this->doorNumber = doorNumber;
}

void Address::setFloor(string floor) {

	this->floor = floor;
}

void Address::setPostalCode(string postalCode) {

	this->postalCode = postalCode;
}

void Address::setLocation(string  location) {

	this->location = location;
}


/*********************************
 * Mostrar Address
 ********************************/

 // discplyes an address in a nice format
ostream& operator<<(ostream& out, const Address & address) {

	out << address.street << " / " << address.doorNumber << " / " << address.floor
		<< address.postalCode << address.location;
	return out;
}
