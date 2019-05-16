#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <iomanip>

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
	packets.reserve(10000);
	if (in_stream.is_open() && fileLen != 0)
	{
		string fileInput;
		getline(in_stream, this->name); // Name
		getline(in_stream, fileInput);
		this->VATnumber = stoi(fileInput); // VAT
		getline(in_stream, this->URL); // URL
		getline(in_stream, fileInput);
		address = Address(fileInput); // To Do: Default Address constructor 
		packetsId = 0; // For test purposes...
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
int Agency::getPacketsId() const
{
	return packetsId;
}

unsigned Agency::getSoldPacksNumber() const
{
	return soldPacksNumber;
}

double Agency::getTotalValue() const
{
	return totalValue;
}

bool& Agency::getClientsInfoHasChanged()
{
	return clientsInfoHasChanged;
}

bool& Agency::getPacketsInfoHasChanged()
{
	return packetsInfoHasChanged;
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
void Agency::setPacketsId(int id)
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
		currentPacket.setSites(sitesNormalization(auxString));
		getline(in_stream, auxString);
		currentPacket.setBeginDate(Date(auxString));
		getline(in_stream, auxString);
		currentPacket.setEndDate(Date(auxString));
		getline(in_stream, auxString);
		currentPacket.setPricePerPerson(stod(auxString));
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
		currentClient.setTotalPurchased(stod(auxString));
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

void Agency::clientCreation(string &explorer)
{
	Client cClient;
	string reader;
	int VAT, house;
	bool vatNDigits = true, vatExistence = true, packetflag = true;

	cout << string(100, '\n');
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
			vatExistence = verifyVATExistence(Aux);
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
	clientsInfoHasChanged = true;
}

string Agency::UpdateAgencyInfo(string &explorer)
{
	string reader;
	int VAT; // It's a temporary variable too
	bool flag = true;
	bool toggle = true;
	int repetition = 0;

	cout << string(100, '\n');
	cout << explorer << endl << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "[Go Back] CTRL+Z" << endl << endl;

	while (toggle)
	{
		if (repetition == 0)
		{
			cout << endl << "What do you want to change?\n";
			repetition++;
		}
		else
			cout << "Do you want to change anything else?\n";
		cout << "1. Agency Name\n2. VAT Number\n3. URL\n4. Address\n0. Back\n\n";
		int option;
		cin >> option; cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (cin.eof())
			return name;
		cout << endl;

		switch (option)
		{
		case 0:
		{
			toggle = false;
			break;
		}
		case 1:
		{
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
			break;
		}
		case 2:
		{
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
			break;
		}
		case 3:
		{
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
		}
		case 4:
		{
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
			break;
		}
		}
		if (toggle)
		{
			cout << endl << "Agency successfully altered!" << endl << endl;
			agencyInfoHasChanged = true;
		}
	}
	return name;
}

void Agency::viewTotalSold(string &explorer) const
{
	cout << string(100, '\n');
	cout << explorer << endl << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl << left << setw(25) << "Number of packs sold: " << soldPacksNumber << endl << left << setw(25) << "Total value: " << totalValue << endl << endl;
}

multimap<int, string, greater<int>> Agency::orderedMostVisited()
{
	map<string, int> sites;
	map<string, int>::iterator iT;
	for (const auto &x : packets)
	{
		int currP = x.getCurrentPersons();
		size_t i = 0;
		if (x.getSitesVector().size() > 1)
		{
			vector<string> auxiliarSites = x.getSitesVector();
			for (i = 1; i < auxiliarSites.size(); i++)
			{
				string auxiliarPlace = auxiliarSites.at(i);
				iT = sites.find(auxiliarPlace);
				if (iT == sites.end())
					sites.insert(pair<string, int>(auxiliarPlace, currP));
				else
					iT->second += currP;
			}
		}
		else
		{
			string auxI = x.getSitesVector().at(0);
			iT = sites.find(auxI);
			if (iT == sites.end())
				sites.insert(pair<string, int>(auxI, currP));
			else
				iT->second += currP;
		}
	}

	multimap<int, string, greater<int>> orderedSites; // greater<int> is a COMPARE
	for (iT = sites.begin(); iT != sites.end(); iT++)
		orderedSites.insert(pair<int, string>(iT->second, iT->first));

	return orderedSites;
}

void Agency::viewMoreVisited(string &explorer)
{
	cout << endl;
	cout << string(100, '\n');
	cout << explorer << endl << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "[Go Back] CTRL+Z" << endl << endl;
	int N;

	multimap<int, string, greater<int>> orderedSites = orderedMostVisited(); // greater<int> is a COMPARE
	N = checkInt("Number of Nth most visited packets: ");
	while (N > orderedSites.size() && !cin.eof())
	{
		cout << "There aren't as many places as you referred... Please select another number." << endl;
		N = checkInt("Number of Nth most visited packets: ");
	}
	if (cin.eof())
		return;

	cout << endl << endl << "\t\t\t" << left << setw(35) << "PLACE" << left << setw(35) << "TRIPS" << endl << endl;

	multimap<int, string, greater<int>>::const_iterator mI = orderedSites.begin();
	int count = 0;
	while (count < N)
	{
		cout << "\t\t\t" << left << setw(35) << mI->second << left << setw(35) << mI->first << endl;
		count++;
		mI++;
	}

	cout << endl << endl;
	if (cin.peek() != EOF)
		cin.ignore(100, '\n');
	cin.get();
	fflush(stdin);
	return;
}

void Agency::viewMoreVisitedForClient(string & explorer)
{
	cout << endl;
	cout << string(100, '\n');
	cout << explorer << endl << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "[Go Back] CTRL+Z" << endl << endl;
	multimap<int, string, greater<int>> orderedSites = orderedMostVisited();
	// cout << endl << endl << setw(25) << "CLIENT" << setw(40) << "RECOMMENDED DESTINATION" << endl << endl;

	multimap<int, string, greater<int>>::iterator mI;

	for (auto &x : clients)
	{
		multimap<int, string, greater<int>> orderedSitesAux = orderedSites;
		for (const auto &y : x.getPacketList())
		{
			for (const auto &w : y->getSitesVector())
			{
				for (mI = orderedSitesAux.begin(); mI != orderedSitesAux.end(); mI++)
				{
					if (w == mI->second)
					{
						orderedSitesAux.erase(mI);
						break;
					}
				}
			}
		}

		if (orderedSitesAux.size() > 0)
		{
			mI = orderedSitesAux.begin();
			cout << "\t\tCLIENT NAME: " << left << setw(25) << x.getName() << "\tRECOMMENDED DESTINATION: " << left << setw(25) << mI->second << endl;// << "------------------------------------------------------------------------------------------------------------------------" << endl;
			/*
			string viewP;
			cout << endl << "View corresponding packet? (Y/N)"; getline(cin, viewP);
			cout << endl << endl;
			bool gotOut = false;
			if (viewP == "y" || viewP == "Y")
			{
				for (const auto &z : packets)
				{
					if (z.getSitesVector().size() > 1)
					{
						vector<string> auxiliarSites = z.getSitesVector();
						for (size_t i = 1; i < auxiliarSites.size(); i++)
						{
							if (auxiliarSites.at(i) == mI->second)
							{
								cout << z << endl;
								gotOut = true;
								break;
							}

						}
						if (gotOut)
							break;
					}
					else
					{
						if (z.getSitesVector().at(0) == mI->second)
						{
							cout << z << endl;
							gotOut = true;
							break;
						}
					}
				}
			}
			*/
			cout << endl << "CORRESPONDING PACK:" << endl << endl;
			bool gotOut = false;

			for (const auto &z : packets)
			{
				if (z.getSitesVector().size() > 1)
				{
					vector<string> auxiliarSites = z.getSitesVector();
					for (size_t i = 1; i < auxiliarSites.size(); i++)
					{
						if (auxiliarSites.at(i) == mI->second)
						{
							cout << z << endl;
							gotOut = true;
							break;
						}

					}
					if (gotOut)
						break;
				}
				else
				{
					if (z.getSitesVector().at(0) == mI->second)
					{
						cout << z << endl;
						gotOut = true;
						break;
					}
				}
			}
		}
		else
			cout << "\t\tCLIENT NAME: " << left << setw(25) << x.getName() << "\tRECOMMENDED DESTINATION: " << left << setw(25) << "NONE" << endl;// << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << endl << endl;
	cin.get();
	fflush(stdin);
	return;
}

void Agency::viewMoreVisitedForSpecificClient(string &explorer)
{
	bool toggle = true;
	string clientName;
	int clientVAT;
	int indexClient, confirm;

	while (toggle)
	{
		indexClient = 0;
		confirm = 0;
		cout << string(100, '\n');
		cout << explorer << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cout << endl << "Name of the Client: "; getline(cin, clientName);
		if (cin.eof())
			return;
		transform(clientName.begin(), clientName.end(), clientName.begin(), toupper);
		for (size_t i = 0; i < size(clients); i++)
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
			cout << endl;
			if (confirmNif != 0 || confirm == 1)
			{
				multimap<int, string, greater<int>> orderedSites = orderedMostVisited();
				multimap<int, string, greater<int>>::iterator mI;
				multimap<int, string, greater<int>> orderedSitesAux = orderedSites;
				Client x = clients.at(indexClient);
				for (const auto &y : x.getPacketList())
				{
					for (const auto &w : y->getSitesVector())
					{
						for (mI = orderedSitesAux.begin(); mI != orderedSitesAux.end(); mI++)
						{
							if (w == mI->second)
							{
								orderedSitesAux.erase(mI);
								break;
							}
						}
					}
				}

				if (orderedSitesAux.size() > 0)
				{
					mI = orderedSitesAux.begin();
					cout << "\t\tCLIENT NAME: " << left << setw(25) << x.getName() << "\tRECOMMENDED DESTINATION: " << left << setw(25) << mI->second << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
					cout << "CORRESPONDING PACK:" << endl << endl;
					bool gotOut = false;

					for (const auto &z : packets)
					{
						if (z.getSitesVector().size() > 1)
						{
							vector<string> auxiliarSites = z.getSitesVector();
							for (size_t i = 1; i < auxiliarSites.size(); i++)
							{
								if (auxiliarSites.at(i) == mI->second)
								{
									cout << z << endl;
									gotOut = true;
									break;
								}

							}
							if (gotOut)
								break;
						}
						else
						{
							if (z.getSitesVector().at(0) == mI->second)
							{
								cout << z << endl;
								gotOut = true;
								break;
							}
						}
					}
				}
				else
					cout << "\t\tCLIENT NAME: " << left << setw(25) << x.getName() << "\tRECOMMENDED DESTINATION: " << left << setw(25) << "NONE" << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;
			}
			else
				cout << "\nFound no user with VAT: " << clientVAT << endl << endl;
		}
		int option;
		cout << "1. See for another client\n0. Main Menu\n\n";
		while ((!(cin >> option) || !(option == 0 || option == 1)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl << "1. See for another client\n0. Main Menu\n\n";
		}
		if (option == 0)
			toggle = false;
	}
	cout << endl;

}

void Agency::viewAllPackets(string &explorer) const
{
	cout << endl;
	cout << string(100, '\n');
	cout << explorer << endl << endl;
	for (size_t i = 0; i < packets.size(); i++)
	{
		if (packets.at(i).getId() >= 0)
		{
			cout << packets.at(i);
			if (i < (packets.size() - 1))
				cout << "-----------------------------------------------------------------------------------------------------------\n";
		}
	}
	return;
}

void Agency::viewPacketByDestination(string &explorer) const
{
	bool toggle = true;
	while (toggle)
	{
		string locationPack;
		bool confirm = true;
		cout << string(100, '\n');
		cout << explorer << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cout << endl << "Destination of the pack: "; getline(cin, locationPack);
		if (cin.eof())
			return;
		cout << endl;
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
						cout << packets.at(i) << endl << endl;
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

void Agency::viewPacketByDate(string &explorer) const
{
	bool toggle = true;
	while (toggle)
	{
		bool confirm = true;
		string date1, date2;

		cout << string(100, '\n');
		cout << explorer << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[Go Back] CTRL+Z" << endl << endl;

		cout << "Beginning date (Year / Month / Day): "; getline(cin, date1);
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
		cout << endl;
		for (unsigned int i = 0; i < packets.size(); i++)
		{
			if (checkBetweenDates(date1, date2, packets.at(i).getBeginDate())
				&& checkBetweenDates(date1, date2, packets.at(i).getEndDate()) && packets.at(i).getId() > 0)
			{
				cout << packets.at(i) << endl << endl;
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

void Agency::viewPacketByDateAndDest(string &explorer) const
{
	bool toggle = true;
	int index, confirmLocation;
	while (toggle)
	{
		string locationPack;
		index = 0;
		confirmLocation = 0;
		cout << string(100, '\n');
		cout << explorer << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cout << endl << endl << "Destination of the pack: "; getline(cin, locationPack); trim(locationPack);
		if (cin.eof())
			return;
		transform(locationPack.begin(), locationPack.end(), locationPack.begin(), toupper);
		vector<int> idxLocation;
		idxLocation.clear();
		for (size_t i = 0; i < packets.size(); i++)
		{
			vector<string> sitesVector = packets.at(i).getSitesVector();
			for (size_t j = 0; j < sitesVector.size(); j++)
			{
				string auxiliar = sitesVector.at(j);
				transform(auxiliar.begin(), auxiliar.end(), auxiliar.begin(), toupper);
				if (auxiliar == locationPack)
				{
					idxLocation.push_back(i);
					confirmLocation++;
					break;
				}
			}
		}
		if (confirmLocation == 0)
			cout << "There is no pack with destination: '" << locationPack << "'!" << endl << endl;
		else
		{
			string date1, date2;
			int confirmDate = 0;
			cout << "Beginning date (Year / Month / Day): "; //cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, date1);
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
			vector <int> idxDate;
			idxDate.clear();
			for (size_t i = 0; i < packets.size(); i++)
			{
				if (checkBetweenDates(date1, date2, packets.at(i).getBeginDate())
					&& checkBetweenDates(date1, date2, packets.at(i).getEndDate()))
				{
					idxDate.push_back(i);
					confirmDate++;
				}
			}
			if (confirmDate == 0)
				cout << "There are no packets within those dates!" << endl << endl;
			else
			{
				vector<int> idxs;
				idxs.clear();
				idxs = vectorIntersec(idxLocation, idxDate);
				cout << endl;
				if (idxs.size() != 0)
				{
					for (size_t i = 0; i < idxs.size(); i++)
					{
						int index = idxs.at(i);

						if (packets.at(index).getId() >= 0)
							cout << packets.at(index) << endl << endl;
					}
				}
				else
					cout << endl << "\nNo packs to show for that location and between those dates\n" << endl << endl;
			}
		}
		int option;
		cout << "1. See another pack by date and destination\n0. Back\n\n"; cin >> option;
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
	while (toggle)
	{
		cout << string(100, '\n');
		cout << explorer << endl << endl;
		packId = 0;
		index = 0;
		confirm = true;
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		packId = checkInt("ID of the pack: ");
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
					refPacket.setSites(sitesNormalization(reader));
					break;
				}
				case 2:
				{
					cout << "Beginning date (Year / Month / Day): "; getline(cin, reader);
					string auxEDate = refPacket.getEndDate().getDate();
					while (((reader.empty() || existingDate(reader)) || endLaterThenBeg(auxEDate, reader)) && !cin.eof())
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
					double price;
					while ((!(cin >> price) || (price < 0)) && !cin.eof())
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
					while ((!(cin >> tMax) || !(tMax >= curPersons)) && !cin.eof())
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
				{
					cout << endl << "Packet successfully altered!" << endl << endl;
					packetsInfoHasChanged = true;
				}
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

void Agency::removePacket(string &explorer)
{
	bool toggle = true;
	char answer;
	while (toggle)
	{
		int packId = 0;
		int index = 0;
		bool confirm = true;
		cout << string(100, '\n');
		cout << explorer << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[Go Back] CTRL+Z" << endl << endl;
		packId = checkInt("ID of the pack: ");
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
				packetsInfoHasChanged = true;
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
			cout << endl << "1. Remove another pack\n0. Main Menu\n\n";
		}
		if (option == 0)
			toggle = false;
		else
			cout << endl;
	}
}

void Agency::viewSoldPacksAccToSpeClient(string &explorer)
{
	bool toggle = true;
	string clientName;
	int clientVAT;
	int indexClient, confirm;
	while (toggle)
	{
		indexClient = 0;
		confirm = 0;
		cout << string(100, '\n');
		cout << explorer << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cout << endl << "Name of the Client: "; getline(cin, clientName);
		if (cin.eof())
			return;
		transform(clientName.begin(), clientName.end(), clientName.begin(), toupper);
		for (size_t i = 0; i < size(clients); i++)
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
			cout << endl;
			if (confirmNif != 0 || confirm == 1)
			{
				for (const auto &x : clients.at(indexClient).getPacketList())
					cout << *x << endl;
			}
			else
				cout << "\nFound no user with VAT: " << clientVAT << endl << endl;
		}
		int option;
		cout << "1. Check another client\n0. Main Menu\n\n";
		while ((!(cin >> option) || !(option == 0 || option == 1)))
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl << "1. Check another client\n0. Main Menu\n\n";
		}
		if (option == 0)
			toggle = false;
	}
	cout << endl;
}

void Agency::viewSoldPacksAccToAllClients(string &explorer)
{
	string viewP;
	cout << string(100, '\n');
	cout << explorer << endl << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "[Go Back] CTRL+Z" << endl << endl;
	// cout << endl << endl << setw(65) << "CLIENT NAME" << setw(25) << "BOUGHT PACKETS" << endl;
	for (auto &x : clients)
	{
		viewP = "";
		cout << endl << "\t\tCLIENT NAME: " << left << setw(25) << x.getName() << "\tBOUGHT PACKETS: " << left << setw(25) << x.getPacketList().size() << endl;
		cout << "--------------------------------------------------------------------------------------------" << endl;
		cout << endl << "View corresponding packets? (Y/N)"; getline(cin, viewP);
		if (cin.eof())
			return;
		if (viewP == "y" || viewP == "Y")
		{
			cout << endl;
			for (const auto &y : x.getPacketList())
			{
				cout << *y << endl;
				cout << "--------------------------------------------------------------------------------------------" << endl;
			}
		}
		cout << endl << endl;
	}
	cout << endl;
}

//CLIENT FUNCTIONS
void Agency::viewAllClients(string &explorer) const
{
	cout << string(100, '\n');
	cout << explorer << endl << endl;
	size_t size = clients.size();
	for (size_t i = 0; i < size; i++)
	{
		cout << clients.at(i);
		if (i < (size - 1))
			cout << "--------------------------------------------------------------------------------------------\n";
	}
	cout << endl;
}

void Agency::viewSpecificClient(string &explorer) const
{
	bool toggle = true;
	while (toggle)
	{
		string clientName;
		int clientVAT;
		int indexClient = 0, confirm = 0;
		cout << string(100, '\n');
		cout << explorer << endl << endl;
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
				cout << endl << clients.at(indexClient) << endl;
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

void Agency::alterClient(string &explorer)
{
	bool toggle = true;
	while (toggle)
	{
		string clientName;
		int clientVAT;
		int indexClient = 0, confirm = 0;

		cout << string(100, '\n');
		cout << explorer << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[Go Back] CTRL+Z" << endl << endl;

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
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
					{
						cout << endl << "Client successfully altered!" << endl << endl;
						clientsInfoHasChanged = true;
					}
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
		cout << string(100, '\n');
		cout << explorer << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[Go Back] CTRL+Z" << endl << endl;
		indexClient = 0;
		confirm = 0;
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
						totalValue -= clients.at(indexClient).getPacketList().at(i)->getPricePerPerson() * clients.at(indexClient).getFamilySize();
						soldPacksNumber -= clients.at(indexClient).getFamilySize();
						clients.at(indexClient).getPacketList().at(i)->setCurrentPersons(clients.at(indexClient).getPacketList().at(i)->getCurrentPersons() - clients.at(indexClient).getFamilySize());
					}
				}
				clients.erase(clients.begin() + indexClient, clients.begin() + indexClient + 1);
				cout << endl << "Client successfully deleted!" << endl << endl;
				clientsInfoHasChanged = true;
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

void Agency::buyPacket(string &explorer)
{
	bool toggle = true;
	int option;

	while (toggle)
	{
		option = -1;
		string clientName;
		int clientVAT;
		int indexClient = 0, confirm = 0;
		cout << string(100, '\n');
		cout << explorer << endl << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "[Go Back] CTRL+Z" << endl << endl;
		cout << endl << "Name of the Client: "; getline(cin, clientName);
		if (cin.eof())
			return;
		transform(clientName.begin(), clientName.end(), clientName.begin(), toupper);
		for (size_t i = 0; i < clients.size(); i++)
		{
			string auxiliar = clients.at(i).getName();
			transform(auxiliar.begin(), auxiliar.end(), auxiliar.begin(), toupper);
			if (auxiliar == clientName)
			{
				confirm++;
				indexClient = i;
			}
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
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (cin.eof())
						return;
					for (size_t i = 0; i < packets.size(); i++)
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
				bool alreadyBought = false;
				vector<Packet*> packetList = clients.at(indexClient).getPacketList();
				for (size_t i = 0; i < packetList.size(); i++)
				{
					if (abs(packetList.at(i)->getId()) == abs(packId))
					{
						alreadyBought = true;
						break;
					}
				}

				if (((packets.at(indexPack).getMaxPersons() - packets.at(indexPack).getCurrentPersons()) >= clients.at(indexClient).getFamilySize()) && !alreadyBought)
				{
					clients.at(indexClient).getPacketList().push_back(&packets.at(indexPack));
					packets.at(indexPack).setCurrentPersons(packets.at(indexPack).getCurrentPersons() + clients.at(indexClient).getFamilySize());
					// clients.at(indexClient).addPacketListIds(packId);
					clients.at(indexClient).setTotalPurchased(clients.at(indexClient).getTotalPurchased() + (packets.at(indexPack).getPricePerPerson() * clients.at(indexClient).getFamilySize()));
					totalValue += packets.at(indexPack).getPricePerPerson() * clients.at(indexClient).getFamilySize();
					soldPacksNumber += clients.at(indexClient).getFamilySize();
					if ((packets.at(indexPack).getMaxPersons() == packets.at(indexPack).getCurrentPersons()))
						packets.at(indexPack).setId(-packId);
					cout << "\nPack successfully bought!" << endl << endl;
					clientsInfoHasChanged = true;
					packetsInfoHasChanged = false;
				}
				else
				{
					if (alreadyBought)
					{
						cout << "\nThis client has already bought this pack!\n" << endl;
					}
					else
					{
						cout << "\nNot enough spots available for this packet!" << " \n----------\n" << endl;
						break;
					}
				}
			}
			else
			{
				cout << "\nFound no user with VAT: " << clientVAT
					<< endl << endl;
			}
		}
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
		if (option == 0)
			toggle = false;
	}
	cout << endl;
}

Agency::~Agency()
{
	string saveReader;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (agencyInfoHasChanged)
	{
		cout << "Save Agency's changes? (Y/N)"; getline(cin, saveReader);
		if (saveReader == "Y" || saveReader == "y")
		{
			// File agency.txt flush
			ofstream out_stream(AGENCY_FILE_NAME);
			if (out_stream.is_open())
			{
				out_stream << name + "\n";
				out_stream << VATnumber << "\n";
				out_stream << URL + "\n";
				out_stream << address.getStreet() + " / " + to_string(address.getDoorNumber()) + " / " + address.getFloor() + " / " + address.getPostalCode() + " / " + address.getLocation() + "\n";

				out_stream << clientsFilename << "\n";
				out_stream << packetsFilename << "\n";
				out_stream.close();
				cout << endl << "Agency's info saved!" << endl << endl;
			}
			else
				cerr << "An error occurred during the process...";
			out_stream.close();
			if (cin.peek() != EOF)
				cin.ignore(100, '\n');
			cin.get();
			fflush(stdin);
		}
	}
	if (clientsInfoHasChanged)
	{
		cout << "Save Clients' changes? (Y/N)"; getline(cin, saveReader);
		if (saveReader == "Y" || saveReader == "y")
		{
			// File clients.txt flush
			ofstream out_stream(clientsFilename);
			if (out_stream.is_open())
			{
				for (size_t j = 0; j < clients.size(); j++)
				{
					out_stream << clients.at(j).getName() + "\n";
					out_stream << clients.at(j).getVATnumber() << "\n";
					out_stream << clients.at(j).getFamilySize() << "\n";
					out_stream << clients.at(j).getAddress().getStreet() + " / " + to_string(clients.at(j).getAddress().getDoorNumber()) + " / " + clients.at(j).getAddress().getFloor() + " / " + clients.at(j).getAddress().getPostalCode() + " / " + clients.at(j).getAddress().getLocation() + "\n";
					string auxiliarIds = "";
					int listSize = clients.at(j).getPacketList().size();
					if (listSize > 0)
					{
						for (size_t i = 0; i < listSize; i++)
						{
							if (i < (listSize - 1))
								auxiliarIds += to_string(clients.at(j).getPacketList().at(i)->getId()) + " ; ";
							else
								auxiliarIds += to_string(clients.at(j).getPacketList().at(i)->getId());
						}
					}
					else
						auxiliarIds = "0";
					out_stream << auxiliarIds << "\n";
					out_stream << clients.at(j).getTotalPurchased() << "\n";
					if (j < (clients.size() - 1))
						out_stream << ":::::::::::\n";
				}
			}
			else
				cerr << "An error occurred during the process...";
			cout << endl << "Clients' info saved!" << endl << endl;
			out_stream.close();
			if (cin.peek() != EOF)
				cin.ignore(100, '\n');
			cin.get();
			fflush(stdin);
		}
	}
	if (packetsInfoHasChanged)
	{
		cout << "Save Packets' changes? (Y/N)"; getline(cin, saveReader);
		if (saveReader == "Y" || saveReader == "y")
		{
			// File packets.txt flush
			ofstream out_stream(packetsFilename);
			if (out_stream.is_open())
			{
				out_stream << to_string(packetsId) + "\n";
				int listSize = packets.size();
				for (size_t j = 0; j < packets.size(); j++)
				{
					out_stream << to_string(packets.at(j).getId()) << "\n";
					out_stream << packets.at(j).getSites() << "\n";
					out_stream << to_string(packets.at(j).getBeginDate().getYear()) + "/" + to_string(packets.at(j).getBeginDate().getMonth()) + "/" + to_string(packets.at(j).getBeginDate().getDay()) << "\n";
					out_stream << to_string(packets.at(j).getEndDate().getYear()) + "/" + to_string(packets.at(j).getEndDate().getMonth()) + "/" + to_string(packets.at(j).getEndDate().getDay()) << "\n";
					out_stream << to_string(packets.at(j).getPricePerPerson()) << "\n";
					out_stream << to_string(packets.at(j).getMaxPersons()) << "\n";
					out_stream << to_string(packets.at(j).getCurrentPersons()) << "\n";
					if (j < (listSize - 1))
						out_stream << ":::::::::::\n";
				}
			}
			else
				cerr << "An error occurred during the process...";
			out_stream.close();
			cout << endl << "Packets' info saved!" << endl << endl;
			if (cin.peek() != EOF)
				cin.ignore(100, '\n');
			cin.get();
			fflush(stdin);
		}
	}
}

/*********************************
 * Mostrar Loja
 ********************************/
ostream& operator<<(ostream& out, const Agency & agency) {

	out << "\t\t\t\tName: " << agency.name << "\n"
		<< "\t\t\t\tVAT Number: " << agency.VATnumber << "\n"
		<< "\t\t\t\tURL: " << agency.URL << "\n"
		<< "\t\t\t\tAddress: " << agency.address << "\n";
	return out;
}


void Agency::packetCreation(string &explorer)
{
	Packet cPacket;
	string reader;
	double price;
	unsigned tMax;
	cout << string(100, '\n');
	cout << explorer << endl << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "[Go Back] CTRL+Z" << endl << endl;

	cout << "Places to visit: "; getline(cin, reader); // Places format -> Porto - Porto, Gaia, Arcozelo | OR | Madeira (only)

	while ((reader.empty() || cPacket.sitesFormat(reader)) && !cin.eof()) // Overload sitesFormat
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Places to visit: "; getline(cin, reader);
	}
	if (cin.eof())
		return;
	trim(reader);
	cPacket.setSites(sitesNormalization(reader));

	cout << "Beginning date (Year / Month / Day): "; getline(cin, reader);
	while ((reader.empty() || existingDate(reader)) && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Beginning date (Year / Month / Day): "; getline(cin, reader);
	}
	if (cin.eof())
		return;
	trim(reader);
	cPacket.setBeginDate(Date(reader));
	string beggining = reader;

	cout << "End date (Year / Month / Day): "; getline(cin, reader);
	while ((reader.empty() || existingDate(reader) || endLaterThenBeg(reader, beggining)) && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "End date (Year / Month / Day): "; getline(cin, reader);
	}
	if (cin.eof())
		return;
	trim(reader);
	cPacket.setEndDate(Date(reader));

	cout << "Price per person: ";
	while (!(cin >> price) && !cin.eof() || (price < 0))
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
	cPacket.setPricePerPerson(price);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Max Lotation: ";
	while (!(cin >> tMax) && !cin.eof())
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
	cPacket.setMaxPersons(tMax);

	int pId = (packetsId + 1);
	cPacket.setId(pId);
	packetsId = pId;
	packetsInfoHasChanged = true;
	packets.push_back(cPacket);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl << "Packet successfully created!" << endl;
	// Construction PACKET
	// Date TemporaryBegin(begD), TemporaryEnd(endD);
	// NewPacket = Packet(sitesNormalization(places), TemporaryBegin, TemporaryEnd, price, tMax);
}