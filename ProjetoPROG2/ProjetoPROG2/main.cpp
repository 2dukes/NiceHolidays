#include <iostream>
#include <string>
#include <vector>

#include "Agency.h"
#include "Menus.h"
// #include "utils.h"

const std::string AGENCY_FILE_NAME = "agency.txt";

int main() {
	/*cout << "Hi,..." << endl;
	system("pause");*/
	Agency agency(AGENCY_FILE_NAME);   // create the agency
	agency.readPackets();
	agency.readClients();
	mainMenu(agency); // initial menu inicial with the major options of the application

	return 0;
}
