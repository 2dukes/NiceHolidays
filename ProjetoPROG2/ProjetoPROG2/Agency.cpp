#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Agency.h"

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
} // retira espacos extra

void decompose(string s, vector<string> &elements, char sep)
{
	size_t pos = s.find(sep);
	while (pos != string::npos)
	{
		string elem = s.substr(0, pos);
		trim(elem);
		elements.push_back(elem);
		s.erase(0, pos + 1);
		pos = s.find(sep);
	}
	trim(s);
	elements.push_back(s);
} // decompoe string a partir de separador


Agency::Agency(string fileName)
{
	/*ifstream agencyfile;
	vector<string> adressElems;
	string adressString;

	decompose(adressString, adressElems, '/');
	getline(agencyfile, this->name);
	agencyfile >> this->VATnumber;
	address.setStreet(adressElems.at(0));
	address.setDoorNumber(stoi(adressElems.at(1)));
	address.setFloor(adressElems.at(2));
	address.setPostalCode(adressElems.at(3));
	address.setLocation(adressElems.at(4));
	getline(agencyfile, this->URL);*/
	
	ifstream in_stream(fileName);
	string fileInput;
	getline(in_stream, this->name); // Name
	getline(in_stream, fileInput);
	this->VATnumber = stoi(fileInput); // VAT
	getline(in_stream, this->URL); // URL
	getline(in_stream, fileInput);
	address = Address(fileInput); // To Do: Default Address constructor 
	getline(in_stream, this->clientsFile);
	getline(in_stream, this->packetsFile);
}

// metodos GET
string Agency::getName() const {

	return this->name;
}

unsigned Agency::getVATnumber() const {

	return this->VATnumber;
}

Address Agency::getAddress() const {

	//  IMPLEMENTATION REQUIRED 
}

string Agency::getURL() const {

	return this->URL;
}

vector<Client> Agency::getClients() const {

	return this->clients;
}

vector<Packet> Agency::getPackets() const {

	return this->packets;
}


// SET Methods

void Agency::setName(string name) {

	//  IMPLEMENTATION REQUIRED 
}

void Agency::setVATnumber(unsigned VATnumber) {

	//  IMPLEMENTATION REQUIRED 
}

void Agency::setAddress(Address address) {

	//  IMPLEMENTATION REQUIRED 
}
void Agency::setURL(string url) {

	//  IMPLEMENTATION REQUIRED 

}
void Agency::setClients(vector<Client> &clients) {

	//  IMPLEMENTATION REQUIRED 

}
void Agency::setPackets(vector<Packet> &packets) {

	//  IMPLEMENTATION REQUIRED 

}

/*********************************
 * Mostrar Loja
 ********************************/

 // mostra o conteudo de uma agencia
ostream& operator<<(ostream& out, const Agency & agency) {

	// A IMPLEMENTATION REQUIRED 
}
