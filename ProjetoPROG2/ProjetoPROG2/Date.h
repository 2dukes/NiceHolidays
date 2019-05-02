#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"

using namespace std;

class Date{
 private:
  unsigned short day;
  unsigned short month;
  unsigned year;

 public:
  Date();
  Date(string date);
  Date(unsigned short day, unsigned short month, unsigned year);

  // GET methods
  unsigned short getDay() const;
  unsigned short getMonth() const;
  unsigned getYear() const;
  
  // SET methods
  
  void setDay(unsigned short day);
  void setMonth(unsigned short month);
  void setYear(unsigned year);

  // outhet methods */
  
  friend ostream& operator<<(ostream& out, const Date & date);

};
