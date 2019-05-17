#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>


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
	int packetsId; // Last inserted ID in packets.txt
	string clientsFilename; // clients file name 
	string packetsFilename; // packets file name
	double totalValue; // total value in sold packs
	unsigned int soldPacksNumber; // number of total sold packs

	bool agencyInfoHasChanged;  // flag that is set to "true" if the agency info has been changed/added/deleted at least once
	bool clientsInfoHasChanged; // flag that is set to "true" if at least one client has been changed/added/deleted
	bool packetsInfoHasChanged; // flag that is set to "true" if at least one packet has been changed/added/deleted

public:
	Agency(string fileName);

	// methods GET
	string getName() const;
	unsigned getVATnumber() const;
	Address getAddress() const;
	string getURL() const;
	const vector<Client>& getClients() const; // get the clients vector
	const vector<Packet>& getPackets() const; // get the packs vector
	int getPacketsId() const; // get the last inserted pack's id
	unsigned getSoldPacksNumber() const;
	double getTotalValue() const;
	bool& getClientsInfoHasChanged();
	bool& getPacketsInfoHasChanged();

	// methods SET
	void readPackets(); // read the packs from the packs file and store them into the packets vector
	void readClients(); // read the clients from the clients file and store them into the clients vector
	void setName(string name); 
	void setVATnumber(unsigned VATnumber);
	void setAddress(Address address);
	void setURL(string url);
	void setClient(Client &client); // add a new client to the clients vector
	//void setClients(vector<Client> & clients); 
	void setPacket(Packet &packet); // add a new pack to the packs vector
	void setPacketsId(int id); // set the new last inserted pack's id

	/*----- other methods -----*/
	bool verifyVATExistence(unsigned &VAT) const; // returns "true" if the VAT number "VAT" isn't present in any other client on the agency
	string UpdateAgencyInfo(string &explorer); // updates the agency info and returns the agency name
	void viewTotalSold(string &explorer) const; // show the total value and number of sold packs
	multimap<int, string, greater<int>> orderedMostVisited(); // returns a multimap with the number of trips and the corresponding site, ordered from the
															  // most visited site to the least visited
	void viewMoreVisited(string &explorer); // view the top N (number specified by the user) most visited places
	void viewMoreVisitedForClient(string &explorer); // view list of all clients and the recommended place to visit and the corresponding pack
	void viewMoreVisitedForSpecificClient(string &explorer); // view the recommended place and corresponding pack to a client indicated by the user

	//Packets
	void viewAllPackets(string &explorer) const; // view all available packs
	void viewPacketByDestination(string &explorer) const; // view all available packs for one specified destination
	void viewPacketByDate(string &explorer) const; // view all available packs between 2 dates
	void viewPacketByDateAndDest(string &explorer) const; // view all available packs between 2 dates and 1 destination
	void alterPack(string &explorer); // alter a pack's info
	void removePacket(string &explorer); // remove a pack (make it unavailable) 
	void viewSoldPacksAccToSpeClient(string &explorer); // view all sold packs to a specified client
	void viewSoldPacksAccToAllClients(string &explorer); // view all sold packs to all clients

	//Clients
	void viewAllClients(string &explorer) const; // view all clients
	void viewSpecificClient(string &explorer) const; // view client specified by user
	void alterClient(string &explorer); // alter a client's info
	void removeClient(string &explorer); // remove a client
	void buyPacket(string &explorer); // buy a pack for a specified client

	~Agency(); // Destructor (used to write the clients and packs data in the files at the end of the program)
	
	// Creations of packs and clients

	void packetCreation(string &explorer); // create a new pack
	void clientCreation(string &explorer); // create a new client

	friend ostream& operator<<(ostream& out, const Agency & agency); // overload of operator << (display the formatted agency on a ostream)
};
