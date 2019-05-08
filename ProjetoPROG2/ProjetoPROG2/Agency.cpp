#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Agency.h"
#include "GeneralFunctions.h"

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
	in_stream.seekg(0, in_stream.end);
	streamsize fileLen = in_stream.tellg();
	in_stream.seekg(0, in_stream.beg);
	if (in_stream.is_open() && fileLen != 0)
	{
		string fileInput;
		getline(in_stream, this->name); // Name
		getline(in_stream, fileInput);
		this->VATnumber = stoi(fileInput); // VAT
		getline(in_stream, this->URL); // URL
		getline(in_stream, fileInput);
		address = Address(fileInput); // To Do: Default Address constructor 
		packetsId = 1; // For test purposes...

	}
	else
	{
		cerr << "An error occurred during the process..." << endl;
		system("pause");
		exit(1);
	}
}

// GET Methods
string Agency::getName() const 
{

	return name;
}
unsigned Agency::getVATnumber() const 
{

	return VATnumber;
}
Address Agency::getAddress() const 
{

	return address;
}
string Agency::getURL() const 
{

	return URL;
}
const vector<Client>& Agency::getClients() const 
{
	return clients;
}
const vector<Packet>& Agency::getPackets() const 
{
	return packets;
}
unsigned Agency::getPacketsId() const
{
	return packetsId;
}

// SET Methods
void Agency::setName(string name) 
{

	this->name = name;
}
void Agency::setVATnumber(unsigned VATnumber) 
{

	this->VATnumber = VATnumber;
}
void Agency::setAddress(Address address) {

	this->address = address;
}
void Agency::setURL(string url) {

	this->URL = url; 
}
void Agency::setClients(vector<Client> &clients) {

	//  IMPLEMENTATION REQUIRED 
}
void Agency::setPacket(Packet &packet) 
{

	packets.push_back(packet);
}
void Agency::setPacketsId(unsigned id)
{
	packetsId = id;
}


//funcoes de ler as informacoes de pacotes e clientes

void Agency::readPackets()
{
	ifstream in_stream("packets.txt");
	string auxString;
	string separator; // separador "::::::::::"
	if (getline(in_stream, auxString))
		packetsId = stoi(auxString);
	while (getline(in_stream, auxString))
	{
		Packet currentPacket; // New Packet each time it iterates
		currentPacket.setId(stoi(auxString));
		getline(in_stream, auxString);
		currentPacket.setSites(currentPacket.sitesNormalization(auxString));
		getline(in_stream, auxString);
		currentPacket.setBeginDate(Date(auxString));
		getline(in_stream, auxString);
		currentPacket.setEndDate(Date(auxString));
		getline(in_stream, auxString);
		currentPacket.setPricePerPerson(stoi(auxString));
		getline(in_stream, auxString);
		currentPacket.setMaxPersons(stoi(auxString));
		getline(in_stream, auxString);
		currentPacket.setCurrentPersons(stoi(auxString));
		getline(in_stream, separator);
		packets.push_back(currentPacket); // Store packet in vector<Packet> packets
	}
	in_stream.close();
}

bool Agency::verifyVATExistence(unsigned &VAT) const
{
	for (const auto &client : clients)
	{
		if (client.getVATnumber() == VAT)
			return false;
	}
	return true;
}

void Agency::clientCreation(string &explorer, Agency &agency)
{
	Client cClient;
	string reader;
	int VAT, house;
	bool vatNDigits = true, vatExistence = true, packetflag = true;

	system("cls");
	cout << explorer << endl << endl;
	// ofstream out_stream("clients.txt", std::ios_base::app);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "-> CTRL+Z to leave..." << endl << endl;
	cout << "Client name: "; getline(cin, reader);
	while (reader.empty() && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Client name: "; getline(cin, reader);
	}
	if (cin.eof())
		return;
	trim(reader);
	cClient.setName(reader);
	// out_stream << reader + "\n";

	do
	{
		cout << "VAT Number: "; cin >> VAT;
		if (cin.eof())
			return;
		if (cin.fail())
		{
			cin.clear();
			cerr << "Invalid Option! Please enter a 9 digit VAT." << endl << endl;
		}
		else
		{
			vatNDigits = VATConfirm(VAT);
			if (vatNDigits)
				cerr << "Invalid Option! Please enter a 9 digit VAT." << endl << endl;
			unsigned Aux = VAT;
			vatExistence = agency.verifyVATExistence(Aux);
			if (!vatExistence)
				cerr << "This VAT already exists..." << endl << endl;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (vatNDigits || !vatExistence);
	cClient.setVATnumber(VAT);

	cout << "Number of people in household: ";
	while (!(cin >> house) && !cin.eof())
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cerr << "Invalid Option! Please enter a valid input." << endl << endl;
		cout << endl << "Number of people in household: ";
	}
	if (cin.eof())
		return;
	cClient.setFamilySize(house);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
	while ((reader.empty() || adrConfirm(reader)) && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
	}
	if (cin.eof())
		return;
	trim(reader);
	Address NewAdress(reader);
	cClient.setAddress(NewAdress);
	// out_stream << reader + "\n";
	// out_stream << reader + "\n";
	// out_stream << reader + "\n";
	// out_stream << "::::::::::\n";

	// out_stream.close();
	clients.push_back(cClient); // Push_Back new client to vector<string> clients
	cout << endl << "Your data was successfully inserted!" << endl << endl;
	system("pause");

}

string Agency::UpdateAgencyInfo(string &explorer)
{
	string reader;
	int VAT; // It's a temporary variable too
	bool flag = true;

	system("cls");
	cout << explorer << endl << endl;
	// ofstream out_stream(AGENCY_FILE_NAME);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "[Go Back] CTRL+Z" << endl << endl;
	cout << "New agency name: "; getline(cin, reader);
	while (reader.empty() && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "New agency name: "; getline(cin, reader);
	}
	if (cin.eof())
		return name;
	trim(reader);
	setName(reader);
	// out_stream << reader + "\n";
	do
	{
		cout << "VAT Number: "; cin >> VAT;
		if (cin.eof())
			return name;
		if (cin.fail())
		{
			cin.clear();
			cerr << "Invalid Option! Please enter a 9 digit VAT." << endl << endl;
		}	
		else
		{
			flag = VATConfirm(VAT);
			if (flag)
				cerr << "Invalid Option! Please enter a 9 digit VAT." << endl << endl;
		}	
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (flag);
	setVATnumber(VAT);
	// out_stream << VAT << "\n";

	cout << "URL: "; getline(cin, reader);
	while (reader.empty() && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "URL: "; getline(cin, reader);
	}
	if (cin.eof())
		return name;
	trim(reader);
	setURL(reader);
	// out_stream << reader + "\n";

	cout << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
	while ((reader.empty() || adrConfirm(reader)) && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
	}
	if (cin.eof())
		return name;
	trim(reader);
	Address NewAdress(reader);
	setAddress(NewAdress);
		
	cout << endl << "Your data was successfully changed!" << endl << endl;
	system("pause");
	/*
	// File agency.txt flush
	ofstream out_stream(AGENCY_FILE_NAME);
	if (out_stream.is_open())
	{
		out_stream << agencyName + "\n";
		out_stream << VAT << "\n";
		out_stream << aUrl + "\n";
		out_stream << adr + "\n";

		out_stream << clientsFilename << "\n";
		out_stream << packetsFilename << "\n";
		out_stream.close();
		cout << endl << "Your data was successfully inserted!" << endl << endl;
	}
	else
		cerr << "An error occurred during the process...";		
	system("pause");
	*/
	return name;
}

void Agency::viewAllPackets() const
{
	int size = packets.size();
	for (size_t i = 0; i < size; i++)
	{
		cout << packets.at(i);
		if (i < (size - 1))
			cout << "::::::::::\n";
	}
}

void Agency::viewAllClients() const
{
	int size = clients.size();
	for (size_t i = 0; i < size; i++)
	{
		cout << clients.at(i);
		if (i < (size - 1))
			cout << "::::::::::\n";
	}
}

/*********************************
 * Mostrar Loja
 ********************************/
ostream& operator<<(ostream& out, const Agency & agency) {

	out << agency.name << "\n"
		<< agency.VATnumber<< "\n"
		<< agency.URL << "\n"
		<< agency.address << "\n";
	return out;
}
