#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Address.h"
#include "Client.h"
#include "Packet.h"
#include "GeneralFunctions.h"

using namespace std;

class Agency {
private:
	string name; // name of the  agency
	unsigned int VATnumber; // VAT number of the agency
	Address address; // address of the agency
	string URL; // URL of the agency Web site
	vector<Client> clients; // vector to store the existing clients
	vector<Packet> packets; // vector to store the existing packets
	unsigned int packetsId; // Last inserted ID in packets.txt
	string clientsFilename; // clients file name 
	string packetsFilename; // packets file name
	double totalValue;
	unsigned int soldPacksNumber;

	bool clientsInfoHasChanged; // flag that is set to "true" if at least one client has been changed/added/deleted
	bool packetsInfoHasChanged; // flag that is set to "true" if at least one packet has been changed/added/deleted
	unsigned int maxClientsId; // maximum value among all clients identifiers
	unsigned int maxPacketsId; // maximum value among all packets identifiers

public:
	Agency(string fileName);

	// methods GET
	string getName() const;
	unsigned getVATnumber() const;
	Address getAddress() const;
	string getURL() const;
	const vector<Client>& getClients() const;
	const vector<Packet>& getPackets() const;
	unsigned getPacketsId() const;
	unsigned getSoldPacksNumber() const;
	unsigned getTotalValue() const;


	// methods SET
	void readPackets();
	void readClients();
	void setName(string name);
	void setVATnumber(unsigned VATnumber);
	void setAddress(Address address);
	void setURL(string url);
	void setClient(Client &client);
	void setClients(vector<Client> & clients);
	void setPacket(Packet &packet);
	void setPacketsId(unsigned id);

	// other methods */
	bool verifyVATExistence(unsigned &VAT) const;
	void clientCreation(string &explorer, Agency &agency);
	string UpdateAgencyInfo(string &explorer);
	void viewAllPackets() const;
	void viewPacketByDestination() const;
	void viewPacketByDate() const;
	void viewPacketByDateAndDest() const;
	void removePacket();
	void viewAllClients() const;
	void viewSpecificClient() const;
	void alterClient();
	void removeClient();
	void buyPacket();
	friend ostream& operator<<(ostream& out, const Agency & agency);
};
