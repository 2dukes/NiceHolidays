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

	while (cin.fail() || !(option >= 0 && option <= (displays.size() - 1)))
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

	system("cls");
	vector<string> mainChoices = { "1. Display Agency Info", "2. Update Agency Info", "3. Manage", "4. View client", "5. View All Clients", "6. View Available Travel Pack(s)", "7. View Sold Travel Pack(s)", "8. Buy Travel Pack", "9. View Total Amount and Number of Sold Travel Packs","10. Show most visited destinations","11. Recommendend Packets for each Client", "0. Exit" };
	vector<string> manageChoices = { "1. Create", "2. Alter", "3. Remove", "0. Main Menu" };
	vector<string> manageSecundaryChoices = { "1. Client(s)", "2. Travel Pack(s)", "0. Previous Menu" };
	vector<string> viewAvailablePackChoices = { "1. All", "2. Acording to Destination", "3. Between 2 Dates", "4. Acording to Destination and 2 Dates", "0. Main Menu" };
	vector<string> viewSoldPackChoices = { "1. Acording to a Specific Client", "2. Acording to All Clients", "0. Main Menu" };

	do
	{
		if (cin.eof())
			cin.clear();

		system("cls");
		cout << agencyName << endl << endl << endl;
		for (size_t i = 0; i < mainChoices.size(); i++)
			cout << "\t" << mainChoices.at(i) << endl;
		cout << endl << endl;
		cout << "Option: "; cin >> mainMenu;

		while (cin.fail() || !(mainMenu >= 0 && mainMenu <= (mainChoices.size() - 1)))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "Invalid Option! Please enter a valid number." << endl << endl;
			cout << "Option: "; cin >> mainMenu;
		}

		switch (mainMenu)
		{
		case 1:
			cout << endl << agency;
			if (cin.peek() != EOF)
				cin.ignore(100, '\n');
			cin.get();
			fflush(stdin);
			break;
		case 2:
			agencyName = agency.UpdateAgencyInfo(mainChoices.at(mainMenu - 1));
			break;
		case 3:
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
							{
								// Create | Client
								string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1);
								agency.clientCreation(auxiliarExplorer);
								cin.get();
								fflush(stdin);
								break;
							}
							case 2:
							{
								// Create | Packs
								//Packet cPacket;
								string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1);
								/*
								cPacket.packetCreation(auxiliarExplorer);
								if(!cin.eof())
								{ 
									int pId = (agency.getPacketsId() + 1);
									cPacket.setId(pId);
									agency.setPacketsId(pId);
									agency.setPacket(cPacket);
									agency.getPacketsInfoHasChanged() = true;
								}
								*/
								agency.packetCreation(auxiliarExplorer);
								cin.get();
								
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
						}
						break;
					case 2:
						switch (option2)
						{
							case 1:
							{
								// Alter | Client
								string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1);
								agency.alterClient(auxiliarExplorer);
								break;
							}
							case 2:
							{
								// Alter | Pack
								string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1);
								agency.alterPack(auxiliarExplorer);
								cin.get();
								fflush(stdin);
								break;
							}
							default:
								break;
						}
						break;
					case 3:
						switch (option2)
						{
							case 1:
							{
								// Remove | Client
								string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1);
								agency.removeClient(auxiliarExplorer);
								cin.get();
								fflush(stdin);
								break;
							}
							case 2:
							{
								// Remove | Pack
								string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + manageChoices.at(option1 - 1) + " | " + manageSecundaryChoices.at(option2 - 1);
								agency.removePacket(auxiliarExplorer);
								break;
							}
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
		case 4:
		{
			// View Specific client
			string auxiliarExplorer = mainChoices.at(mainMenu - 1);
			agency.viewSpecificClient(auxiliarExplorer);
			break;
		}
		case 5:
		{
			// View All Clients
			string auxiliarExplorer = mainChoices.at(mainMenu - 1);
			agency.viewAllClients(auxiliarExplorer);
			if (cin.peek() != EOF)
				cin.ignore(100, '\n');
			cin.get();
			fflush(stdin);
			break;
		}
		case 6:
		{
			option = displays(viewAvailablePackChoices, mainChoices.at(mainMenu - 1), agencyName);
			switch (option)
			{
			case 1:
			{
				// View All Available Packs
				string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + viewAvailablePackChoices.at(option - 1);
				agency.viewAllPackets(auxiliarExplorer);
				if (cin.peek() != EOF)
					cin.ignore(100, '\n');
				cin.get();
				fflush(stdin);
				break;
			}
			case 2:
			{
				// View Available Packs according to Destination
				string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + viewAvailablePackChoices.at(option - 1);
				agency.viewPacketByDestination(auxiliarExplorer);
				break;
			}
			case 3:
			{
				// View Available Packs according to 2 Dates
				string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + viewAvailablePackChoices.at(option - 1);
				agency.viewPacketByDate(auxiliarExplorer);
				break;
			}
			case 4:
			{
				// View Available Packs according to 2 Dates & Destination
				string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + viewAvailablePackChoices.at(option - 1);
				agency.viewPacketByDateAndDest(auxiliarExplorer);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 7:
			option = displays(viewSoldPackChoices, mainChoices.at(mainMenu - 1), agencyName);
			switch (option)
			{
			case 1:
			{
				// View Bought Packs according to a Specific Client
				string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + viewSoldPackChoices.at(option - 1);
				agency.viewSoldPacksAccToSpeClient(auxiliarExplorer);
				break;
			}
			case 2:
			{
				//View Bought Packs according to all clients
				string auxiliarExplorer = mainChoices.at(mainMenu - 1) + " | " + viewSoldPackChoices.at(option - 1);
				agency.viewSoldPacksAccToAllClients(auxiliarExplorer);
				cin.get();
				fflush(stdin);
				break;
			}
			default:
				break;
			}
			break;
		case 8:
		{
			// Buy Packet
			string auxiliarExplorer = mainChoices.at(mainMenu - 1);
			agency.buyPacket(auxiliarExplorer);
			cin.get();
			fflush(stdin);
			break;
		}
		case 9:
		{
			// View Sold Packets and amount of money made
			string auxiliarExplorer = mainChoices.at(mainMenu - 1);
			agency.viewTotalSold(auxiliarExplorer);
			cin.get();
			fflush(stdin);
			break;
		}
		case 10: 
		{ 
			// View Most Nth visited places
			string auxiliarExplorer = mainChoices.at(mainMenu - 1);
			agency.viewMoreVisited(auxiliarExplorer);
			break;
		}
		case 11:
		{
			// Recommended packets according to each client
			string auxiliarExplorer = mainChoices.at(mainMenu - 1);
			agency.viewMoreVisitedForClient(auxiliarExplorer);
			break;
		}
		default:
			break;
		}
	} while (mainMenu != 0);
}

