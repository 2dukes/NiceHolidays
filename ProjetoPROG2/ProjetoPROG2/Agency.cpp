#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Agency.h"
#include "GeneralFunctions.h"

void decompose(string s, vector<string> &elements, char sep)
{
	size_t pos = s.find(sep);
	while (pos != string::npos)
	{
		string elem = s.substr(0, pos);
		//trim(elem);
		elements.push_back(elem);
		s.erase(0, pos + 1);
		pos = s.find(sep);
	}
	//trim(s);
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
	}
	else
	{
		cerr << "An error occurred during the process..." << endl;
		system("pause");
		exit(1);
	}
}

// metodos GET
string Agency::getName() const {

	return name;
}

unsigned Agency::getVATnumber() const {

	return VATnumber;
}

Address Agency::getAddress() const {

	return address;
}

string Agency::getURL() const {

	return URL;
}

vector<Client> Agency::getClients() const {

	return clients;
}

vector<Packet> Agency::getPackets() const {

	return packets;
}


// SET Methods

void Agency::setName(string name) {

	this->name = name;
	//  IMPLEMENTATION REQUIRED 
}

void Agency::setVATnumber(unsigned VATnumber) {

	this->VATnumber = VATnumber;
	//  IMPLEMENTATION REQUIRED 
}

void Agency::setAddress(Address address) {

	this->address = address;
	//  IMPLEMENTATION REQUIRED 
}
void Agency::setURL(string url) {

	this->URL = url;
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

string Agency::UpdateAgencyInfo(string &explorer)
{
	string reader, aName;
	int VAT;
	bool flag = true;

	system("cls");
	cout << explorer << endl << endl;
	ofstream out_stream(AGENCY_FILE_NAME);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (out_stream.is_open())
	{
		cout << "New agency name: "; getline(cin, reader);
		while (reader.empty())
		{
			cerr << "Invalid Option! Please enter a valid input." << endl;
			cout << endl << "New agency name: "; getline(cin, reader);
		}
		trim(reader);
		aName = reader;
		out_stream << reader + "\n";
		do
		{
			cout << "VAT Number: "; cin >> VAT;
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
		out_stream << VAT << "\n";

		cout << "URL: "; getline(cin, reader);
		while (reader.empty())
		{
			cerr << "Invalid Option! Please enter a valid input." << endl;
			cout << endl << "URL: "; getline(cin, reader);
		}
		trim(reader);
		out_stream << reader + "\n";

		cout << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
		while (reader.empty() || adrConfirm(reader))
		{
			cerr << "Invalid Option! Please enter a valid input." << endl;
			cout << endl << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
		}
		trim(reader);
		
		out_stream << reader + "\n";

		out_stream << "clients.txt\n";
		out_stream << "packs.txt\n";
		out_stream.close();

		cout << endl << "Your data was successfully inserted!" << endl << endl;
		system("pause");
	}
	else
	{
		cerr << "An error occurred during the process...";
		system("pause");
	}
	return aName;
}

 // mostra o conteudo de uma agencia
ostream& operator<<(ostream& out, const Agency & agency) {

	out << agency.name << "\n"
		<< agency.VATnumber<< "\n"
		<< agency.URL << "\n"
		<< agency.address << "\n";
	return out;
}
