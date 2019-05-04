#include <iostream>
#include <string>
#include <fstream>

#include "UpdateAgencyInfo.h"
#include "agency.h"
using namespace std;

void agencyInfoUpdate(string explorer)
{
	string reader;
	bool flag;

	system("cls");
	cout << explorer << endl << endl;
	ofstream out_stream(AGENCY_FILE_NAME);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (out_stream.is_open())
	{
		cout << "New agency name: "; getline(cin, reader);
		while (reader.empty())
			cerr << "Invalid Option! Please enter a valid input." << endl; cout << endl << "New agency name: "; getline(cin, reader);
		trim(reader);
		out_stream << reader + "\n";

		/*do
			{
				cout << "VAT Number: "; getline(cin, reader);
				flag = tifConfirm(reader);
				if (flag)
					cerr << "Invalid Option! Please enter a 9 digit VAT." << endl << endl;
			} while (flag || reader.empty());
			trim(reader);
			out_stream << reader + "\n";

			cout << "URL: "; getline(cin, reader);
			while (reader.empty())
			{
				cerr << "Invalid Option! Please enter a valid input." << endl;
				cout << endl << "URL: "; getline(cin, reader);
			}
			trim(reader);
			out_stream << reader + "\n";

			cout << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
			while (reader.empty() || adrConfirm(reader))
			{
				cerr << "Invalid Option! Please enter a valid input." << endl;
				cout << endl << "Address (Street / Door Number / Floor / Zip Code / Location): "; getline(cin, reader);
			}
			trim(reader);
			out_stream << reader + "\n";

			out_stream << "clients.txt\n";
			out_stream << "packs.txt\n";
			out_stream.close();

			cout << endl << "Your data was successfully inserted!" << endl << endl;
			system("pause");
		}
		else
		{
			cerr << "An error occurred during the process...";
			system("pause");
		}*/
	}
}