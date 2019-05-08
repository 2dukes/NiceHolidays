#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Packet.h"
#include "Address.h"

using namespace std;

class Client{
 private:
  string name; // name of the client
  unsigned VATnumber; // VAT number of client
  unsigned short familySize;  // number of family members
  Address address; // client's address  
  vector<Packet*> packets; // vector to store client's packets bought
  unsigned totalPurchased; // total value spent by the client
  vector<int> ids; //ids of the packets the client bought

 public:
  Client(); // Default Constructor
  Client(string name, unsigned VATnumber, unsigned short familySize, Address address);  // for a new client
  Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<Packet*> & packets, unsigned totalPurchased);  // client read from file

  // GET methods
  
  string getName() const;
  unsigned getVATnumber() const;
  unsigned short getFamilySize() const;
  Address getAddress() const;
  vector<Packet> getPacketList() const;
  unsigned getTotalPurchased() const;
  
  // SET methods
  
  void setName(string name);
  void setVATnumber(unsigned VATnumber);
  void setFamilySize(unsigned short familySize);
  void setAddress(Address address);
  void setPacketListIds(string idsString);
  void setPacketList(vector<Packet> & packets);
  void setTotalPurchased(unsigned totalPurchased);
  
  // other methods
  friend ostream& operator<<(ostream& out, const Client & client);
};
