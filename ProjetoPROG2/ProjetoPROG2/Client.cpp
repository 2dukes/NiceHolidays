#include "Client.h"

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address) // New client
{
	this->name = name;
	this->VATnumber = VATnumber;
	this->familySize = familySize;
	this->address = address;
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
void Client::setTotalPurchased(unsigned totalPurchased){
  
	this->totalPurchased = totalPurchased;
}
  
  // outros metodos

/*void clientCreation(string explorer)
{
	string reader;
	int VAT;
	bool vatNDigits = true, vatExistence = true, packetflag = true, flag = true;

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
			// vatExistence = verifyTIFExistence(reader);
			if (!vatExistence)
				cerr << "This VAT already exists..." << endl << endl;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (vatNDigits || vatExistence);

	cout << "Number of people in household: "; getline(cin, reader);
	while (reader.empty() && !cin.eof())
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Number of people in household: "; getline(cin, reader);
	}
	trim(reader);

	cout << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
	while (reader.empty() || adrConfirm(reader))
	{
		cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
	}
	trim(reader);
	// out_stream << reader + "\n";

	cout << "Bought Packet IDs (1; 2; 3): "; getline(cin, reader);
	packetflag = true;
	if (!reader.empty())
		packetflag = packetBoughtConfirm(reader);
	while (reader.empty() || packetflag)
	{
		if (packetflag)
			cerr << "Packet(s) not found!" << endl;
		else
			cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Bought Packet IDs: "; getline(cin, reader);
		if (!reader.empty())
			packetflag = packetBoughtConfirm(reader);
	}
	vector<int> ids = Normalization(reader);
	trim(reader);
	// out_stream << reader + "\n";

	// TO DO: FUNCTION UPDATE PACKS.TXT !!!!!!! CAN BE USED IN THE 2nd FUNCTION OF INI.H
	cout << "Purchases per Packet (2; 4; 1): "; getline(cin, reader);
	purchaseResponse purchase;
	if (!reader.empty())
		purchase = purchaseConfirm(reader, ids);
	// cout << purchase.result << reader.empty();
	while (reader.empty() || purchase.result)
	{
		if (purchase.result)
		{
			cout << "We've found some problems in your purchase..." << endl;
			for (size_t k = 0; k < purchase.i.size(); k++)
				cout << "Packet " << purchase.i.at(k) << " only has " << purchase.p.at(k) << " available vacancies!" << endl;
		}
		else
			cerr << "Invalid Option! Please enter a valid input." << endl;
		cout << endl << "Purchases per Packet (2; 4; 1): "; getline(cin, reader);
		if (!reader.empty())
			purchase = purchaseConfirm(reader, ids);
	}
	trim(reader);
	// out_stream << reader + "\n";
	// out_stream << "::::::::::\n";

	// out_stream.close();

	cout << endl << "Your data was successfully inserted!" << endl << endl;
	system("pause");

}*/

ostream& operator<<(ostream& out, const Client & client){

  // REQUIRES IMPLEMENTATION 
  return out;
}
