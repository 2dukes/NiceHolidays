#include <sstream>
#include "Address.h"


Address::Address(string adr) 
{
	istringstream iS(adr);
	string adrInfo;
	int auxiliar;
    // Rua Sem Nome / 100 / - / 4400-345 / Porto
	// Suppose that file format is alright
	getline(iS, this->street, '/'); // Street
	getline(iS, adrInfo, '/');
	auxiliar = stoi(adrInfo);
	this->doorNumber = static_cast<unsigned short> (auxiliar); // doorNumber
	getline(iS, this->floor, '/');  // floor
	getline(iS, this->postalCode, '/'); // postalCode
	getline(iS, this->location); // location
}

Address::Address(string street, unsigned short doorNumber, string floor, string postalCode, string location) {

	// REQUIRES IMPLEMENTATION
}

// metodos GET


string Address::getStreet() const {

	// REQUIRES IMPLEMENTATION
}

unsigned short Address::getDoorNumber() const {

	// REQUIRES IMPLEMENTATION
}

string Address::getFloor() const {

	// REQUIRES IMPLEMENTATION
}

string Address::getPostalCode() const {

	// REQUIRES IMPLEMENTATION
}

string Address::getLocation() const {

	// REQUIRES IMPLEMENTATION
}


// metodos SET

void Address::setStreet(string street) {

	// REQUIRES IMPLEMENTATION
}

void Address::setDoorNumber(unsigned short doorNumber) {

	// REQUIRES IMPLEMENTATION
}

void Address::setFloor(string floor) {

	// REQUIRES IMPLEMENTATION
}

void Address::setPostalCode(string postalCode) {

	// REQUIRES IMPLEMENTATION
}

void Address::setLocation(string  location) {

	// REQUIRES IMPLEMENTATION
}


/*********************************
 * Mostrar Address
 ********************************/

 // discplyes an address in a nice format
ostream& operator<<(ostream& out, const Address & address) {

	// REQUIRES IMPLEMENTATION

}
