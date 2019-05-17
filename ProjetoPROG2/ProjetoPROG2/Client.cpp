#include <iomanip>
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

vector<Packet*>& Client::getPacketList()
{
	return packets;
}

double Client::getTotalPurchased() const{
  
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
int Client::setPacketList(string ids, vector<Packet> &packets)
{
	size_t pos = ids.find(';');
	int auxInt;
	int count = 0;
	// cout << this->packets.size() << endl;
	while (pos != string::npos)
	{
		string elem = ids.substr(0, pos);
		auxInt = stoi(elem);
		for (size_t i = 0; i < packets.size(); i++)
		{
			if (packets.at(i).getId() == auxInt)
			{ 
				this->packets.push_back(&packets.at(i)); // POINTER ON!
				count += familySize;
			}
		}
		ids.erase(0, pos + 1);
		pos = ids.find(';');
	}
	auxInt = stoi(ids);
	for (size_t i = 0; i < packets.size(); i++)
	{
		if (packets.at(i).getId() == auxInt)
		{ 
			this->packets.push_back(&packets.at(i)); // POINTER ON!
			count += familySize;	
		}
	}
	return count;
}

void Client::setTotalPurchased(double totalPurchased){
  
	this->totalPurchased = totalPurchased;
}
  
  // Another METHODS


ostream& operator<<(ostream& out, const Client & client){

	out << left << setw(30) << "Name: " << client.name << endl
		<< left << setw(30) << "VAT number: " << client.VATnumber << endl
		<< left << setw(30) << "Family Size: " << client.familySize << endl
		<< left << setw(30) << "Address: " << client.address << endl
		<< left << setw(30) << "Purchased packets: ";
	/*vector<int> ids = client.ids;
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
	}*/
	vector<Packet*> clientPackets = client.packets;
	size_t size = clientPackets.size();
	if (size > 0)
	{
		for (size_t i = 0; i < size; i++)
		{
			/*cout << client.packets.at(i)->getId() << endl;
			system("pause");*/
			if (i < (size - 1))
				out << clientPackets.at(i)->getId() << " ; ";
			else
				out << clientPackets.at(i)->getId() << endl;
		}
	}
	else out << "0" << endl;
	
	out << left << setw(30) << "Total amount spent: " << client.totalPurchased << endl;
	return out;
}
