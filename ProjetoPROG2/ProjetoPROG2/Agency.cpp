#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Agency.h"
#include "GeneralFunctions.h"

using namespace std;

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

unsigned Agency::getSoldPacksNumber() const
{
	return soldPacksNumber;
}

unsigned Agency::getTotalValue() const
{
	return totalValue;
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
	totalValue = 0;
	soldPacksNumber = 0;
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
		soldPacksNumber += currentClient.setPacketList(auxString, packets);
		getline(in_stream, auxString);
		currentClient.setTotalPurchased(stoi(auxString));
		totalValue += stoi(auxString); // Agency variable
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

	cout << "[Go Back] CTRL+Z" << endl << endl;
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
	bool toggle = true;
	while (toggle)
	{
		string locationPack;
		bool confirm = true;
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cout << endl << "Destination of the pack: "; cin.ignore(numeric_limits<streamsize>::max(), '\n'); getline(cin, locationPack);
		if (cin.eof())
			return;
		trim(locationPack);
		transform(locationPack.begin(), locationPack.end(), locationPack.begin(), toupper);
		for (unsigned int i = 0; i < packets.size(); i++)
		{
			for (auto x : packets.at(i).getSitesVector())
			{
				string auxiliar = x;
				transform(auxiliar.begin(), auxiliar.end(), auxiliar.begin(), toupper);
				if (auxiliar == locationPack)
				{ 
					if (packets.at(i).getId() > 0)
					{
						cout << packets.at(i);
						confirm = false;
					}
				}
			}
		}
		if (confirm)
			cout << "There is no pack with destination '" << locationPack << "'!" << endl << endl;
		int option;
		cout << endl << "1. See another pack by destination\n0. Back\n\n"; 
		while ((!(cin >> option) || !(option == 0 || option == 1)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl << "1. See another pack by destination\n0. Back\n\n";
		}
		if (option == 0)
			toggle = false;		
	}
}

void Agency::viewPacketByDate() const
{
	bool toggle = true;
	while (toggle)
	{
		bool confirm = true;
		// vector<int> idx;
		// idx.clear();
		string date1, date2;
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cout << "Beginning date (Year / Month / Day): "; cin.ignore(numeric_limits<streamsize>::max(), '\n'); getline(cin, date1);
		while ((date1.empty() || existingDate(date1)) && !cin.eof())
		{
			cerr << "Invalid Option! Please enter a valid input." << endl;
			cout << endl << "Beginning date (Year / Month / Day): "; getline(cin, date1);
		}
		if (cin.eof())
			return;
		cout << "End date (Year / Month / Day): "; getline(cin, date2);
		while ((date2.empty() || existingDate(date2) || endLaterThenBeg(date2, date1)) && !cin.eof())
		{
			cerr << "Invalid Option! Please enter a valid input." << endl;
			cout << endl << "End date (Year / Month / Day): "; getline(cin, date2);
		}
		if (cin.eof())
			return;
		for (unsigned int i = 0; i < packets.size(); i++)
		{
			if (checkBetweenDates(date1, date2, packets.at(i).getBeginDate())
				&& checkBetweenDates(date1, date2, packets.at(i).getEndDate()) && packets.at(i).getId() > 0)
			{
				cout << packets.at(i);
				confirm = false;
			}
		}
		if (confirm)
			cout << "There is no pack within those dates!" << endl << endl;
		int option;
		cout << "1. See another pack by date\n0. Back\n\n";
		while ((!(cin >> option) || !(option == 0 || option == 1)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl << "1. See another pack by destination\n0. Back\n\n";
		}
		if (option == 0)
			toggle = false;
	}
}

void Agency::removePacket()
{
	bool toggle = true;
	char answer;
	while (toggle)
	{
		int packId = 0;
		int index = 0;
		bool confirm = true;
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    packId = checkInt("ID of the pack: ");
		if (cin.eof())
			return;
		for (unsigned int i = 0; i < size(packets); i++)
		{
			if (packets.at(i).getId() == packId && packets.at(i).getId() > 0)
			{
				index = i;
				confirm = false;
			}
		}
		if (confirm)
			cout << "There is no registered available pack with ID '" << packId << "'!" << endl << endl;
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
				cout << "\nPack not removed!" << endl << endl;
		}
		int option;
		cout << "1. Remove another pack\n0. Main Menu\n\n";
		while ((!(cin >> option) || !(option == 0 || option == 1)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl << "1. See another pack by destination\n0. Back\n\n";
		}
		if (option == 0)
			toggle = false;
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
	bool toggle = true;
	while (toggle)
	{
		string clientName;
		int clientVAT;
		int indexClient = 0, confirm = 0;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cout << endl << "Name of the Client: "; getline(cin, clientName);
		if (cin.eof())
			return;
		transform(clientName.begin(), clientName.end(), clientName.begin(), toupper);
		for (unsigned int i = 0; i < size(clients); i++)
		{
			string auxiliar = clients.at(i).getName();
			transform(auxiliar.begin(), auxiliar.end(), auxiliar.begin(), toupper);
			if (auxiliar == clientName)
			{
				indexClient = i;
				confirm++;
			}
		}
		if (confirm == 0)
			cout << "There is no registered client named '" << clientName << "'!" << endl << endl;
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
					if (cin.eof())
						return;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					valid = VATConfirm(clientVAT);
					if (!valid)
						cerr << "Invalid Option! Please enter a 9 digit VAT." << endl;
				} while (!valid);

				for (unsigned int i = 0; i < size(clients); i++)
				{
					if (clients.at(i).getVATnumber() == clientVAT)
					{
						indexClient = i;
						confirmNif++;
					}
				}
			}
			if (confirmNif != 0 || confirm == 1)
				cout << clients.at(indexClient) << endl;
			else
				cout << "\nFound no user with VAT: " << clientVAT << endl << endl;
		}
		int option;
		cout << "1. See another client\n0. Main Menu\n\n";
		while ((!(cin >> option) || !(option == 0 || option == 1)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl << "1. See another pack by destination\n0. Back\n\n";
		}
		if (option == 0)
			toggle = false;
	}
	cout << endl;
}

void Agency::alterClient()
{
	bool toggle = true;
	while (toggle)
	{
		string clientName;
		int clientVAT;
		int indexClient = 0, confirm = 0;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Name of the Client: "; getline(cin, clientName);
		if (cin.eof())
			return;
		transform(clientName.begin(), clientName.end(), clientName.begin(), toupper);
		for (size_t i = 0; i < clients.size(); i++)
		{
			string auxiliar = clients.at(i).getName();
			transform(auxiliar.begin(), auxiliar.end(), auxiliar.begin(), toupper);
			if (auxiliar == clientName)
			{
				indexClient = i;
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
					if (cin.eof())
						return;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					valid = VATConfirm(clientVAT);
					if (!valid)
						cerr << "Invalid Option! Please enter a 9 digit VAT." << endl;
				} while (!valid);

				for (unsigned int i = 0; i < size(clients); i++)
				{
					if (clients.at(i).getVATnumber() == clientVAT)
					{
						indexClient = i;
						confirmNif++;
					}
				}
			}
			if (confirmNif != 0 || confirm == 1)
			{
				cout << endl << clients.at(indexClient) << endl;
				bool toggle2 = true;
				int repetition = 0;
				string reader;
				int VAT;
				bool vatNDigits = true, vatExistence = true;
				while (toggle2)
				{
					if (repetition == 0)
					{
						cout << endl << "What do you want to change?\n";
						repetition++;
					}
					else
						cout << "Do you want to change anything else?\n";
					cout << "1. Name\n2. VAT number\n3. Household\n4. Address\n0. Back\n\n";
					int option;
					cin >> option; cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << endl;

					switch (option)
					{
					case 0:
						toggle2 = false;
						break;
					case 1:
						cout << "New Client name: "; getline(cin, reader);
						while (reader.empty() && !cin.eof())
						{
							cerr << "Invalid Option! Please enter a valid input." << endl;
							cout << endl << "New Client name: "; getline(cin, reader);
						}
						if (cin.eof())
							return;
						trim(reader);
						clients.at(indexClient).setName(reader);
						cout << endl;
						break;
					case 2:
						do
						{
							cout << "New VAT Number: "; cin >> VAT;
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
								vatExistence = verifyVATExistence(Aux);
								if (!vatExistence)
									cerr << "This VAT already exists..." << endl << endl;
							}
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						} while (vatNDigits || !vatExistence);
						clients.at(indexClient).setVATnumber(VAT);
						cout << endl;
						break;
					case 3:
						clients.at(indexClient).setFamilySize(checkInt("New Household: "));
						cout << endl;
						break;
					case 4:
						cout << "New Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
						while ((reader.empty() || adrConfirm(reader)) && !cin.eof())
						{
							cerr << "Invalid Option! Please enter a valid input." << endl;
							cout << endl << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
						}
						if (cin.eof())
							return;
						trim(reader);
						// Address NewAdress(reader);
						clients.at(indexClient).setAddress(Address(reader));
						break;
					}
					if (toggle2)
						cout << endl << "Client successfully altered!" << endl << endl;
				}
			}
			else
				cout << "\nFound no user with VAT: " << clientVAT << " !" << endl << endl;
		}
		int option;
		cout << "1. Change another client\n0. Main Menu\n\n"; 
		while ((!(cin >> option) || !(option == 0 || option == 1)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl << "1. See another pack by destination\n0. Back\n\n";
		}
		if (option == 0)
			toggle = false;
		else
			cout << endl;
	}
	cout << endl;
}

void Agency::removeClient(string &explorer)
{
	bool toggle = true;
	string clientName;
	int clientVAT;
	int indexClient, confirm;
	while (toggle)
	{
		system("cls");
		cout << explorer << endl << endl;
		indexClient = 0;
		confirm = 0;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Name of the Client: "; getline(cin, clientName);
		if (cin.eof())
			return;
		transform(clientName.begin(), clientName.end(), clientName.begin(), toupper);
		for (size_t i = 0; i < clients.size(); i++)
		{
			string auxiliar = clients.at(i).getName();
			transform(auxiliar.begin(), auxiliar.end(), auxiliar.begin(), toupper);
			if (auxiliar == clientName)
			{
				indexClient = i;
				confirm++;
			}
		}
		if (confirm == 0)
			cout << "There is no registered client named " << clientName << "!" << endl << endl;
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
					if (cin.eof())
						return;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					valid = VATConfirm(clientVAT);
					if (!valid)
						cerr << "Invalid Option! Please enter a 9 digit VAT." << endl;
				} while (!valid);

				for (size_t i = 0; i < clients.size(); i++)
				{
					if (clients.at(i).getVATnumber() == clientVAT)
					{
						indexClient = i;
						confirmNif++;
					}
				}
			}
			if (confirmNif != 0 || confirm == 1)
			{
				cout << endl << clients.at(indexClient) << endl;
				bool toggle2 = true;
				int auxiliarID;

				for (size_t i = 0; i < clients.at(indexClient).getPacketList().size(); i++)
				{
					auxiliarID = clients.at(indexClient).getPacketList().at(i)->getId();
					if (auxiliarID > 0)
					{ 
						totalValue -= clients.at(indexClient).getPacketList().at(i)->getPricePerPerson();
						soldPacksNumber--;
						cout << clients.at(indexClient).getPacketList().at(i)->getCurrentPersons() << endl;
						clients.at(indexClient).getPacketList().at(i)->setCurrentPersons(clients.at(indexClient).getPacketList().at(i)->getCurrentPersons() - 1);
						cout << clients.at(indexClient).getPacketList().at(i)->getCurrentPersons() << endl;
					}
				}
				clients.erase(clients.begin() + indexClient, clients.begin() + indexClient + 1);
				cout << endl << "Client successfully deleted!" << endl << endl;
			}
			else
				cout << "\nFound no user with VAT: " << clientVAT << " !" << endl << endl;
		}
		int option;
		cout << "1. Remove another client\n0. Main Menu\n\n";
		while ((!(cin >> option) || !(option == 0 || option == 1)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl << "1. Remove another client\n0. Main Menu\n\n";
		}
		if (option == 0)
			toggle = false;
		else
			cout << endl;
	}
	cout << endl;
}

void Agency::buyPacket()
{
	bool toggle = true;
	int option;
	while (toggle)
	{
		option = -1;
		string clientName;
		int clientVAT;
		int indexClient = 0, confirm = 0;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Name of the Client: "; getline(cin, clientName);
		if (cin.eof())
			return;
		transform(clientName.begin(), clientName.end(), clientName.begin(), toupper);
		for (size_t i = 0; i < clients.size(); i++)
		{
			string auxiliar = clients.at(i).getName();
			transform(auxiliar.begin(), auxiliar.end(), auxiliar.begin(), toupper);
			if (auxiliar == clientName)
				confirm++;
		}
		if (confirm == 0)
			cout << "There is no registered client named '" << clientName << "'!" << endl << endl;
		else
		{
			int confirmNif = 0;
			if (confirm > 1)
			{
				cout << "\nThere are " << confirm << " clients with that name.\nPlease refer the client's VAT: ";
				bool valid;
				do
				{
					cin >> clientVAT;
					if (cin.eof())
						return;
					if (cin.fail())
					{
						cin.clear();
						cerr << "Invalid Option! Please enter a 9 digit VAT." << endl << endl;
					}
					else
					{
						valid = VATConfirm(clientVAT);
						if (valid)
							cerr << "Invalid Option! Please enter a 9 digit VAT." << endl << endl;
					}
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (valid);

				for (unsigned int i = 0; i < size(clients); i++)
				{
					if (clients.at(i).getVATnumber() == clientVAT)
					{
						indexClient = i;
						confirmNif++;
					}
				}
			}
			if (confirmNif != 0 || confirm == 1)
			{
				int confirm = 0, packId = 0, indexPack;
				while (confirm == 0)
				{
					packId = checkInt("ID of the pack: ");
					if (cin.eof())
						return;
					for (size_t i = 0; i < size(packets); i++)
					{
						if (packets.at(i).getId() == packId && packets.at(i).getId() > 0)
						{
							indexPack = i;
							confirm++;
						}
					}
					if (confirm == 0)
						cout << "There are no registered available pack with ID '" << packId << "'!" << endl << endl;
				}
				do
				{
					if ((packets.at(indexPack).getMaxPersons() - packets.at(indexPack).getCurrentPersons()) >= 1)
					{
						clients.at(indexClient).getPacketList().push_back(&packets.at(indexPack));
						packets.at(indexPack).setCurrentPersons(packets.at(indexPack).getCurrentPersons() + 1);
						// clients.at(indexClient).addPacketListIds(packId);
						clients.at(indexClient).setTotalPurchased(clients.at(indexClient).getTotalPurchased() + packets.at(indexPack).getPricePerPerson());
						totalValue += packets.at(indexPack).getPricePerPerson();
						soldPacksNumber += 1;
						if ((packets.at(indexPack).getMaxPersons() == packets.at(indexPack).getCurrentPersons()))
							packets.at(indexPack).setId(-packId);
						cout << "\nPack successfully bought!" << endl << endl;
					}
					else
					{ 
						cout << "\nNot enough spots available for this packet." << " !\n----------\n" << endl;
						break;
					}
				
					cout << "1. Buy another pack\n2. See another client\n0. Main Menu\n\n";
					while ((!(cin >> option) || !(option == 0 || option == 1 || option == 2)))
					{
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
						cout << endl << "1. Buy another pack\n2. See another client\n0. Main Menu\n\n";
					}
				} while (option == 1);
			}
			else
			{
				cout << "\nFound no user with VAT: " << clientVAT
					<< endl << endl;
			}
		}
		if(option != 0 && option != 2)
		{ 
			cout << "1. Buy pack for other client\n0. Main Menu\n\n";
			while ((!(cin >> option) || !(option == 0 || option == 1)))
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << endl << "1. Buy pack for other client\n0. Main Menu\n\n";
			}
		}
		if (option == 0)
			toggle = false;
	}
	cout << endl;
}

void Agency::alterPack(string &explorer)
{
	bool toggle = true, confirm;
	int packId;
	int index;
	char answer;
	while (toggle)
	{
		system("cls");
		cout << explorer << endl << endl;
		packId = 0;
		index = 0;
		confirm = true;
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		packId = checkInt("ID of the pack: ");
		if (cin.eof())
			return;
		for (size_t i = 0; i < packets.size(); i++)
		{
			if (packets.at(i).getId() == packId && packets.at(i).getId() > 0)
			{
				index = i;
				confirm = false;
			}
		}
		if (confirm)
			cout << "There is no registered available pack with ID '" << packId << "'!" << endl << endl;
		else
		{
			cout << endl << packets.at(index) << endl;
			bool toggle2 = true;
			int repetition = 0;
			string reader;
			Packet &refPacket = packets.at(index);
			while (toggle2)
			{
				if (repetition == 0)
				{
					cout << endl << "What do you want to change?\n";
					repetition++;
				}
				else
					cout << "Do you want to change anything else?\n";
				cout << "1. Places to visit\n2. Beginning date\n3. End date\n4. Price per Person\n5. Max Lotation\n0. Back\n\n";
				int option;
				cin >> option; cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << endl;

				switch (option)
				{
					case 0:
					{
						toggle2 = false;
						break;
					}
					case 1:
					{
						cout << "New places to visit: "; getline(cin, reader); // Places format -> Porto - Porto, Gaia, Arcozelo | OR | Madeira (only)
					
						while ((reader.empty() || refPacket.sitesFormat(reader)) && !cin.eof()) // Overload sitesFormat
						{
							cerr << "Invalid Option! Please enter a valid input." << endl;
							cout << endl << "New places to visit: "; getline(cin, reader);
						}
						if (cin.eof())
							return;
						trim(reader);
						refPacket.setSites(refPacket.sitesNormalization(reader));
						break;
					}
					case 2:
					{
						cout << "Beginning date (Year / Month / Day): "; getline(cin, reader);
						string auxEDate = refPacket.getEndDate().getDate();
						while ((reader.empty() || existingDate(reader)) || endLaterThenBeg(auxEDate, reader) && !cin.eof())
						{
							cerr << "Invalid Option! Please enter a valid input." << endl;
							cout << endl << "Beginning date (Year / Month / Day): "; getline(cin, reader);
						}
						if (cin.eof())
							return;
						trim(reader);
						refPacket.setBeginDate(Date(reader));
						break;
					}
					case 3:
					{
						cout << "End date (Year / Month / Day): "; getline(cin, reader);
						string auxBDate = refPacket.getBeginDate().getDate();
						while ((reader.empty() || existingDate(reader) || endLaterThenBeg(reader, auxBDate)) && !cin.eof())
						{
							cerr << "Invalid Option! Please enter a valid input." << endl;
							cout << endl << "End date (Year / Month / Day): "; getline(cin, reader);
						}
						if (cin.eof())
							return;
						trim(reader);
						refPacket.setEndDate(Date(reader));
						break;
					}
					case 4:
					{
						cout << "Price per person: ";
						int price;
						while (!(cin >> price) && !cin.eof())
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							cerr << "Invalid Option! Please enter a valid input." << endl << endl;
							cout << endl << "Price per person: ";
						}
						if (cin.eof())
							return;
						refPacket.setPricePerPerson(price);
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						break;
					}
					case 5:
					{
						int tMax = -1;
						cout << "Max Lotation: ";
						int curPersons = refPacket.getCurrentPersons();
						while (!(cin >> tMax) || !(tMax >= curPersons) && !cin.eof())
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							cerr << "Invalid Option! Please enter a valid input." << endl << endl;
							cout << endl << "Max Lotation: ";
						}
						if (cin.eof())
							return;
						refPacket.setMaxPersons(tMax);
						break;
					}
				}
				if (toggle2)
					cout << endl << "Client successfully altered!" << endl << endl;
			}
			if (refPacket.getCurrentPersons() == refPacket.getMaxPersons())
				refPacket.setId(-packId);
		}
		int option;
		cout << "1. Alter another pack\n0. Main Menu\n\n";
		while ((!(cin >> option) || !(option == 0 || option == 1)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl << "1. Alter another pack\n0. Main Menu\n\n";
		}
		if (option == 0)
			toggle = false;
		else
			cout << endl;
	}
}

/*********************************
 * Mostrar Loja
 ********************************/
ostream& operator<<(ostream& out, const Agency & agency) {

	out << agency.name << "\n"
		<< agency.VATnumber << "\n"
		<< agency.URL << "\n"
		<< agency.address << "\n";
	return out;
}
