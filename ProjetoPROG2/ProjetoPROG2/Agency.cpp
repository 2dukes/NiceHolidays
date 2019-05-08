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
		//packetsId = 1; // For test purposes...
		getline(in_stream, clientsFilename);
		getline(in_stream, packetsFilename);
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

void Agency::setClient(Client &client)
{
	clients.push_back(client);
}

void Agency::setClients(vector<Client> &clients) {

	//  IMPLEMENTATION REQUIRED 
}
void Agency::setPacket(Packet packet) 
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
	ifstream in_stream(packetsFilename);
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
		setPacket(currentPacket); // Store packet in vector<Packet> packets
	}
	in_stream.close();
}

void Agency::readClients()
{
	ifstream in_stream(clientsFilename);
	string auxString;
	string separator; // separador "::::::::::"
	while (getline(in_stream, auxString))
	{
		Client currentClient; // New Packet each time it iterates
		currentClient.setName(auxString);
		getline(in_stream, auxString);
		currentClient.setVATnumber(stoi(auxString));
		getline(in_stream, auxString);
		currentClient.setFamilySize(stoi(auxString));
		getline(in_stream, auxString);
		currentClient.setAddress(Address(auxString));
		getline(in_stream, auxString);
		currentClient.setPacketListIds(auxString);
		getline(in_stream, auxString);
		currentClient.setTotalPurchased(stoi(auxString));
		setClient(currentClient); // Store packet in vector<Packet> packets
		getline(in_stream, separator);
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
	cout << endl;
	for (size_t i = 0; i < size; i++)
	{
		if (packets.at(i).getId() >= 0)
		{
			cout << packets.at(i);
			if (i < (size - 1))
				cout << "::::::::::\n";
		}
	}
	cout << endl;
}

void Agency::viewPacketByDestination() const
{
	int toggle = 0;
	while (toggle == 0)
	{
		string locationPack;
		int index = 0, confirm = 0;
		cout << endl << "Destination of the pack: "; cin.ignore(); getline(cin, locationPack); trim(locationPack);
		vector<int> idx;
		for (unsigned int i = 0; i < size(packets); i++)
		{
			if (packets.at(i).getSitesVector().at(0) == locationPack)
			{
				idx.push_back(i);
				confirm++;
			}
		}
		if (confirm == 0)
		{
			cout << "There is no pack with destination '" << locationPack << "'!"
				<< endl << endl;
		}
		else
		{
			for (unsigned int i = 0; i < size(idx); i++)
			{
				int index = idx.at(i);
				if (packets.at(index).getId() >= 0)
					cout << packets.at(index);
			}
		}
		int option;
		cout << endl << "1. See another pack by destination\n0. Back\n\n"; cin >> option;
		if (option == 0)
			toggle = 1;
	}
}

void Agency::viewPacketByDate() const
{
	int toggle = 0;
	while (toggle == 0)
	{
		int confirm = 0;
		vector<int> idx;
		idx.clear();
		string date1, date2;
		cout << "Beginning date (Year / Month / Day): "; cin.ignore(); getline(cin, date1);
		while ((date1.empty() || existingDate(date1)) && !cin.eof())
		{
			cerr << "Invalid Option! Please enter a valid input." << endl;
			cout << endl << "Beginning date (Year / Month / Day): "; getline(cin, date1);
		}
		cout << "End date (Year / Month / Day): "; getline(cin, date2);
		while ((date2.empty() || existingDate(date2) || endLaterThenBeg(date2, date1)) && !cin.eof())
		{
			cerr << "Invalid Option! Please enter a valid input." << endl;
			cout << endl << "End date (Year / Month / Day): "; getline(cin, date2);
		}
		for (unsigned int i = 0; i < size(packets); i++)
		{
			if (checkBetweenDates(date1, date2, packets.at(i).getBeginDate())
				&& checkBetweenDates(date1, date2, packets.at(i).getEndDate()))
			{
				idx.push_back(i);
				confirm++;
			}
		}
		if (confirm == 0)
		{
			cout << "There is no pack within those dates!"
				<< endl << endl;
		}
		else
		{
			for (unsigned int i = 0; i < size(idx); i++)
			{
				int index = idx.at(i);
				if (packets.at(index).getId() >= 0)
				{
					cout << packets.at(index) << endl;
				}
			}
		}
		int option;
		cout << "1. See another pack by date\n0. Back\n\n"; cin >> option;
		if (option == 0)
			toggle = 1;
	}
	cout << endl;
}

void Agency::removePacket()
{
	int toggle = 0;
	char answer;
	while (toggle == 0)
	{
		int packId = 0;
		int index = 0, confirm = 0;
		string destinations, date;
		cout << "ID of the pack: "; packId = checkInt();
		for (unsigned int i = 0; i < size(packets); i++)
		{
			if (packets.at(i).getId() == packId && packets.at(i).getId() > 0)
			{
				index = i;
				confirm++;
			}
		}
		if (confirm == 0)
		{
			cout << "There is no registered available pack with ID '" << packId << "'!"
				<< endl << endl;
		}
		else
		{
			cout << endl << packets.at(index) << endl
				 << "Are you sure you want to remove this pack?(y/n) "; cin >> answer;
			if (answer == 'y')
			{
				packets.at(index).setId(-packId);
				cout << "\nPack removed!" << endl;
			}
			else
			{
				cout << "\nPack not removed!"
					 << endl << endl;
			}
		}
		int option;
		cout << "1. Remove another pack\n0. Main Menu\n\n"; cin >> option;
		if (option == 0)
			toggle = 1;
		else
			cout << endl;
	}
}

//CLIENT FUNCTIONS
void Agency::viewAllClients() const
{
	size_t size = clients.size();
	for (size_t i = 0; i < size; i++)
	{
		cout << clients.at(i);
		if (i < (size - 1))
			cout << "::::::::::\n";
	}
	cout << endl;
}

void Agency::viewSpecificClient() const
{
	int toggle = 0;
	while (toggle == 0)
	{
		string clientName;
		int clientVAT;
		int index = 0, confirm = 0;
		cin.ignore();
		cout << endl << "Name of the Client: "; getline(cin, clientName);
		for (unsigned int i = 0; i < size(clients); i++)
		{
			if (clients.at(i).getName() == clientName)
			{
				index = i;
				confirm++;
			}
		}
		if (confirm == 0)
		{
			cout << "There is no registered client named '" << clientName << "'!"
				<< endl << endl;
		}
		else
		{
			int confirmNif = 0;
			if (confirm > 1)
			{
				cout << "\nThere are " << confirm << " clients with that name.\nPlease refer the client's NIF: ";
				bool valid;
				do
				{
					cin >> clientVAT;
					valid = VATConfirm(clientVAT);
					if (!valid)
						cerr << "Invalid Option! Please enter a 9 digit VAT." << endl;
				} while (!valid);

				for (unsigned int i = 0; i < size(clients); i++)
				{
					if (clients.at(i).getVATnumber() == clientVAT)
					{
						index = i;
						confirmNif++;
					}
				}
			}
			if (confirmNif != 0 || confirm == 1)
				cout << clients.at(index) << endl;
			else
			{
				cout << "\nFound no user with NIF " << clientVAT
					 << endl << endl;
			}
		}
		int option;
		cout << "1. See another client\n0. Main Menu\n\n"; cin >> option;
		if (option == 0)
			toggle = 1;
	}
	cout << "\n----------\n";
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
