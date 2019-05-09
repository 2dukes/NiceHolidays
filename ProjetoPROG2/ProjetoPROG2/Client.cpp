#include "Client.h"
#include "GeneralFunctions.h"

Client::Client() // New client
{
	name = "Unknown";
	totalPurchased = 0;
}

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address) // New client
{
	this->name = name;
	this->VATnumber = VATnumber;
	this->familySize = familySize;
	this->address = address;
	totalPurchased = 0;
}

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<Packet*> &packets, unsigned totalPurchased) // Client read from file
{
	this->name = name;
	this->VATnumber = VATnumber;
	this->familySize = familySize;
	this->address = address;
	this->packets = packets; // Could be replaced
	this->totalPurchased = totalPurchased;
}

  // GET methods

string Client::getName() const{
  
	return name;
}
  
unsigned Client::getVATnumber() const{
  
	return VATnumber;
}

unsigned short Client::getFamilySize() const{
  
	return familySize;
}

Address Client::getAddress() const{
  
	return address;
}

//vector<Packet> Client::getPacketList() const{
//  
//	// return packets; // -> Could be changed
//}

vector<int> Client::getPacketListIds() const
{
	return ids;
}

unsigned Client::getTotalPurchased() const{
  
	return totalPurchased;
}
  
  // metodos SET
	  
void Client::setName(string name){
  
	this->name = name;
}

void Client::setVATnumber(unsigned VATnumber){
  
	this->VATnumber = VATnumber;
}

void Client::setFamilySize(unsigned short familySize){
  
	this->familySize = familySize;
}
void Client::setAddress(Address address){
  
	this->address = address;
}
void Client::setPacketList(vector<Packet> & packets){
  
	// this->packets = packets;
	// Maybe we'll work with pointers...
}

void Client::setPacketListIds(string idsString)
{
	decomposeToInt(idsString, ids, ';');
}

void Client::addPacketListIds(unsigned id)
{
	ids.push_back(id);
}

void Client::setTotalPurchased(unsigned totalPurchased){
  
	this->totalPurchased = totalPurchased;
}
  
  // Another METHODS


ostream& operator<<(ostream& out, const Client & client){

	out << "Name: " << client.name << endl
		<< "VAT number: " << client.VATnumber << endl
		<< "Family Size: " << client.familySize << endl
		<< "Address: " << client.address << endl
		<< "Purchased packets: ";
	vector<int> ids = client.ids;
	if (client.ids.size() > 0)
	{
		for (size_t i = 0; i < ids.size(); i++)
		{
			if (i < (ids.size() - 1))
				out << ids.at(i) << " ; ";
			else
				out << ids.at(i);
		}
		out << endl;
	}
	/*
	if (client.packets.size() > 0)
	{
		for (const auto &x : client.packets)
			out << x->getId();
	}
	*/
	else out << "0" << endl;
	
	out << "Total amount spent: " << client.totalPurchased << endl;
	//string name; // name of the client
	//unsigned VATnumber; // VAT number of client
	//unsigned short familySize;  // number of family members
	//Address address; // client's address  
	//vector<Packet*> packets; // vector to store client's packets bought
	//unsigned totalPurchased; // total value spent by the client
	return out;
}
