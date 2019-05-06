#include <fstream>
#include "Menus.h"

int displays(vector<string> &displays, string explorer, string &agencyName)
{
	int option;

	system("cls");
	explorer = agencyName + " | " + explorer;
	cout << explorer << endl << endl << endl;
	for (size_t i = 0; i < displays.size(); i++)
		cout << "\t" << displays.at(i) << endl;
	cout << endl << endl;
	cout << "Option: "; cin >> option;

	while (cin.fail() || !(option >= 0 && option <= displays.size() - 1))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cerr << "Invalid Option! Please enter a valid number." << endl << endl;
		cout << "Option: "; cin >> option;
	}

	return option;
}

void mainMenu(Agency &agency) {

	int option, mainMenu, option1, option2;
	string agencyName = agency.getName();

	/*readWriteClientSt();
	readWritePackSt();
	verifyPackValidity();
*/ 
	system("cls");
	vector<string> mainChoices = { "1. Update Agency Info", "2. Manage", "3. View client", "4. View All Clients", "5. View Available Travel Pack(s)", "6. View Sold Travel Pack(s)", "7. Buy Travel Pack", "8. View Total Amount and Number of Sold Travel Packs","9. Show most visited destinations","10. Temp", "0. Exit" };
	vector<string> manageChoices = { "1. Create", "2. Alter", "3. Remove", "0. Main Menu" };
	vector<string> manageSecundaryChoices = { "1. Client(s)", "2. Travel Pack(s)", "0. Previous Menu" };
	vector<string> viewAvailablePackChoices = { "1. All", "2. Acording to Destination", "3. Between 2 Dates", "4. Acording to Destination and 2 Dates", "0. Main Menu" };
	vector<string> viewSoldPackChoices = { "1. Acording to a Specific Client", "2. Acording to All Clients", "0. Main Menu" };

	do
	{
		system("cls");
		cout << agencyName << endl << endl << endl;
		for (size_t i = 0; i < mainChoices.size(); i++)
			cout << "\t" << mainChoices.at(i) << endl;
		cout << endl << endl;
		cout << "Option: "; cin >> mainMenu;

		while (cin.fail() || !(mainMenu >= 0 && mainMenu <= mainChoices.size() - 1))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "Invalid Option! Please enter a valid number." << endl << endl;
			cout << "Option: "; cin >> mainMenu;
		}

		switch (mainMenu)
		{
		case 1:
			agencyName = agency.UpdateAgencyInfo(mainChoices.at(mainMenu - 1));
			cin.clear();
			break;
		case 2:
			while (true)
			{
				option1 = displays(manageChoices, mainChoices.at(mainMenu - 1), agencyName);
				if (option1 != 0)
					option2 = displays(manageSecundaryChoices, mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1), agencyName);
				else
					break;
				if (option2 != 0)
				{
					// 3rd menu functions
					switch (option1)
					{
					case 1:
						switch (option2)
						{
						case 1:
							// Create | Client

							//clientCreation(mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1));
							// Update packs.txt
							//vectorToFile_Packs();
							// Update vclients
							//readWriteClientSt();
							break;
						case 2:
							// Create | Packs
							Packet cPacket;
							string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1);
							cPacket.packetCreation(auxiliarExplorer);
							if (cin.eof())
							{ 
								cin.clear();
								break;
							}
							int pId = agency.getPacketsId() + 1;
							cPacket.setId(pId);
							agency.setPacketsId(pId);
							agency.setPacket(cPacket);
							// Update packets.txt file . . .

							/*ofstream out_stream("packets.txt", std::ios_base::app);
							if (out_stream.is_open())
							{
								int pId = agency.getPacketsId() + 1;
								agency.setPacketsId(pId);
								cPacket.setId(pId);
								out_stream << pId << "\n";
								out_stream << cPacket.getSites() + "\n";
								out_stream << cPacket.getBeginDate().getDate() + "\n";
								out_stream << cPacket.getEndDate().getDate() + "\n";
								out_stream << cPacket.getPricePerPerson() << "\n";
								out_stream << cPacket.getMaxPersons() << "\n";
								out_stream << "::::::::::\n";
								out_stream.close();
								cout << endl << "Your data was successfully inserted!" << endl << endl;
							}
							else
								cerr << "An error occurred during the process...";
							system("pause");*/
							//packscreation(mainchoices.at(mainmenu - 1) + " | " + managechoices.at(option1 - 1) + " | " + managesecundarychoices.at(option2 - 1));
							// update vpacks
							//readwritepackst();
							
							break;
						}
						break;
					case 2:
						switch (option2)
						{
						case 1:
							// Alter | Client
							//clientAlter(mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1));
							// Update packs.txt
							//vectorToFile_Packs();
							// Update clients.txt
							//vectorToFile_Clients();
							break;
						case 2:
							// Alter | Pack
							//packAlter(mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1));
							// Update packs.txt
							// vectorToFile_Packs();
							break;
						default:
							break;
						}
						break;
					case 3:
						switch (option2)
						{
						case 1:
							// Remove | Client
							//clientRemove(mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1));
							// Update clients.txt
							//vectorToFile_Clients();
							break;
						case 2:
							// Remove | Pack
							//packRemove(mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1));
							// Update packs.txt
							//vectorToFile_Packs();
							//system("pause");
							//readWritePackSt();
							break;
						default:
							break;
						}
						break;
					default:
						break;
					}
					break;
				}
			}
			break;
		case 3:
			// View Specific client
			//viewSpecificClient(mainChoices.at(mainMenu - 1));
			break;
		case 4:
			// View All Clients
			//viewAllClients(mainChoices.at(mainMenu - 1));
			break;
		case 5:
			option = displays(viewAvailablePackChoices, mainChoices.at(mainMenu - 1), agencyName);
			switch (option)
			{
			case 1:
				// View All Available Packs
				//viewall(mainChoices.at(mainMenu - 1) + " | " + viewAvailablePackChoices.at(option - 1));
				
				agency.viewAllPackets();
				system("pause");
				break;
			case 2:
				// View Available Packs according to Destination
				//viewADestination(mainChoices.at(mainMenu - 1) + " | " + viewAvailablePackChoices.at(option - 1));
				break;
			case 3:
				// View Available Packs according to 2 Dates
				//viewADate(mainChoices.at(mainMenu - 1) + " | " + viewAvailablePackChoices.at(option - 1));
				break;
			case 4:
				// View Available Packs according to 2 Dates & Destination
				//viewDateDest(mainChoices.at(mainMenu - 1) + " | " + viewAvailablePackChoices.at(option - 1));
				break;
			default:
				break;
			}
			break;
		case 6:
			option = displays(viewSoldPackChoices, mainChoices.at(mainMenu - 1), agencyName);
			switch (option)
			{
			case 1:
				// View Bought Packs according to a Specific Client
				//viewSpPack(mainChoices.at(mainMenu - 1) + " | " + viewSoldPackChoices.at(option - 1));
				break;
			case 2:
				//viewAllBoughtPacks(mainChoices.at(mainMenu - 1) + " | " + viewSoldPackChoices.at(option - 1));
				break;
			default:
				break;
			}
			break;
		case 7:
			//buypacket(mainChoices.at(mainMenu - 1));
			// Update packs.txt
			//vectorToFile_Packs();
			// Update clients.txt
			//vectorToFile_Clients();
			break;
		case 8:
			//amountAndNumberOfSoldPacks(mainChoices.at(mainMenu - 1));
			break;
		case 9:
			break;
		case 10:
			break;
		default:
			break;
		}
	} while (mainMenu != 0);
	
	// A IMPLEMENTAR

	
}

