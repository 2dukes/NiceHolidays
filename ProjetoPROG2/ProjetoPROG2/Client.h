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
  double totalPurchased; // total value spent by the client

 public:
  Client(); // Default Constructor
  Client(string name, unsigned VATnumber, unsigned short familySize, Address address);  // for a new client
  Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<Packet*> & packets, unsigned totalPurchased);  // client read from file

  // GET methods
  
  string getName() const;
  unsigned getVATnumber() const;
  unsigned short getFamilySize() const;
  Address getAddress() const;
  vector<Packet*>& getPacketList(); // get the vector of pointers to bought packs
  double getTotalPurchased() const; // get the total value spent by the client on bought packs
  
  // SET methods

  void setName(string name);
  void setVATnumber(unsigned VATnumber);
  void setFamilySize(unsigned short familySize);
  void setAddress(Address address);
  int setPacketList(string ids, vector<Packet> &packets); // set the vector of pointers to bought packs and returns the total number of bought packs
  void setTotalPurchased(double totalPurchased); // set the total value spent by the client on bought packs
  
  // other methods
  friend ostream& operator<<(ostream& out, const Client & client); // overload of operator << (display the formatted client on a ostream)
};
