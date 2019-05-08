#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Date.h"

using namespace std;

class Packet{
 private:
  int id; // packet unique identifier
  vector<string> sites; // touristic sites to visit
  Date begin;  // begin date
  Date end;  // end date
  double pricePerPerson; // price per person
  unsigned maxPersons; // number of persons still available in the packet (updated whenever the packet is sold to a new client)
  unsigned currentPersons; // Current number of people that embrace the packet

 public:
  Packet(vector<string> sites, Date begin, Date end, double pricePerPerson, unsigned maxPersons);
  Packet();
  // GET methods
  int getId() const;
  string getSites() const; // Return sites in a string format
  vector<string> getSitesVector() const; // Return sites in a vector of strings
  Date getBeginDate() const;
  Date getEndDate() const;
  double getPricePerPerson() const;
  unsigned getMaxPersons() const;

  // SET methods
  void setId(int id);  // to set negative if "deprecated"
  void setSites(vector<string> sites);
  void setBeginDate(Date begin);
  void setEndDate(Date end);
  void setPricePerPerson(double pricePerPerson);
  void setMaxPersons(unsigned maxPersons);
  void setCurrentPersons(unsigned takenTickets);

  // other methods
  bool sitesFormat(string &sitesStr);
  vector<string> sitesNormalization(string &sitesStr);
  void packetCreation(string &explorer);
  friend ostream& operator<<(ostream& out, const Packet & packet);
};
