/*
*****************************************************************************

  File        : main.cpp

  See LICENSE for code licensing.

*****************************************************************************
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdint>
#include<string>

using namespace std;

string names[9] = { "Gunslinger",
	"Frenzy",
	"Demolition",
	"Technician",
	"Marksman",
	"Regulator",
	"Endurance",
	"Guardian",
	"War Hero" };

void edit(string cmd, bool &done);
void editmedals(string filename);
void editstats(string filename);

string backupfile(void);

#define numberofbytesinfile 4357 // last offset 4356=0x1104
#define medalsstart 1404 // 0x57c
#define medalsend 1422 // 0x58d
#define statsstart 3980 // 0xf8c
#define statend 3991 // 0xf97
// each medal two bytes
// stats 4 bytes
/*
	Medal Order:
	Gunslinger
	Frenzy
	Demolition
	Technician
	Marksman
	Regulator
	Endurance
	Guardian
	War Hero
*/
/*
	Stat Order:
	Player Points
	Kills
	Deaths
*/

int main(void){

	string c; // command
	bool exit = false;

	do
	{
		cout << endl;
		cout << "Star Wars Battlefront II Classic Profile Editor. Select a fleet to Command: " << endl;
		cout << "m: edit medals | s: edit stats | e: exit" << endl;
		cout << "Enter command: ";
		getline(cin, c);
		cout << endl;

		edit(c, exit);

	} while (!exit);

	system("cls");

	return 0;
}

void edit(string cmd, bool &leave) {
	string filename;

	if (cmd == "e") {
		leave = true;
		return;
	}
	else {
		filename = backupfile();
	}


	if (cmd == "m") {
		editmedals(filename);
	}
	if (cmd == "s") {
		editstats(filename);
	}
}

void editmedals(string filename){

	ifstream inFile;
	size_t size = 0; // here

	inFile.open(filename, ios::in | ios::binary | ios::ate);
	//char* oData = 0;

	inFile.seekg(0, ios::end); // set the pointer to the end
	size = inFile.tellg(); // get the length of the file
	cout << "Size of file: " << size << endl;
	inFile.seekg(0, ios::beg); // set the pointer to the beginning

	//print data
	//for (size_t i = 0; i < strlen(oData); i++)
	//{
	//	cout << "oData[" << i << "] " << oData[i];
	//	cout << oData[i] << " + 'a' = " << (oData[i] + 'a');
	//
	//}

	// load file into string, easy to view for debugging
	string fullfile;
	fullfile.reserve(size);
	fullfile.assign((istreambuf_iterator<char>(inFile)),
		istreambuf_iterator<char>());

	/* Separate data into parts
		// part 1: name and extraneous
		// part 2: medals
		// part 3: extraneous to stats and beyond
	*/
	string p1;
	string medals;
	string p3;

	p1 = fullfile.substr(0, medalsstart);
	medals = fullfile.substr(medalsstart, medalsend - medalsstart);
	p3 = fullfile.substr(medalsend);

	/* Decode medals string
		// split each medal from string
		// decode medal and store in var
	*/
	char const *c = medals.c_str(); // am I efficient now?
	uint16_t umed[9]; // haha nope 

	/*
	uint16_t Gunslinger = ((uint8_t)c[1] << 8) | (uint8_t)c[0];
	uint16_t Frenzy = ((uint8_t)c[3] << 8) | (uint8_t)c[2];
	uint16_t Demolition = ((uint8_t)c[5] << 8) | (uint8_t)c[4];
	uint16_t Technician = ((uint8_t)c[7] << 8) | (uint8_t)c[6];
	uint16_t Marksman = ((uint8_t)c[9] << 8) | (uint8_t)c[8];
	uint16_t Regulator = ((uint8_t)c[11] << 8) | (uint8_t)c[10];
	uint16_t Endurance = ((uint8_t)c[13] << 8) | (uint8_t)c[12];
	uint16_t Guardian = ((uint8_t)c[15] << 8) | (uint8_t)c[14];
	uint16_t WarHero = ((uint8_t)c[17] << 8) | (uint8_t)c[16];
	*/

	for (int k = 0; k < 9; k++) {
		umed[k] = ((uint8_t)c[k*2+1] << 8) | (uint8_t)c[k*2];
	}

	for (;;) {
		system("cls");

		cout << endl;
		cout << "Career Medals" << endl;
		cout << endl;
		cout << "Gunslinger" << "\t\t" << umed[0] << "\t" << "Technician" << "\t\t" << umed[3] << endl;
		cout << "Demolition" << "\t\t" << umed[2] << "\t" << "Marksman" << "\t\t" << umed[4] << endl;
		cout << "Regulator" << "\t\t" << umed[5] << "\t" << "Endurance" << "\t\t" << umed[6] << endl;
		cout << "Guardian" << "\t\t" << umed[7] << "\t" << "War Hero" << "\t\t" << umed[8] << endl;
		cout << "Frenzy" << "\t\t\t" << umed[1] << endl;
		cout << endl;

		cout << "Change or no change?" << endl;
		cout << "c: change medal count\t e: exit to main menu" << endl;
		string answer;
		getline(cin, answer);

		if (answer == "e") {
			break;
		}
		if (answer == "c") {
			string input = "";

			cout << "Select new medal counts." << endl; // a map would be handy
			for (int i = 0; i < 9; i++) {
				cout << names[i] << ": ";
				getline(cin, input);
				cout << endl;

				stringstream myStream(input);
				myStream >> umed[i];
			}
		}
	}
}

void editstats(string filename){
	

}

string backupfile(void){

	cout << "Enter filename only (ex: Player 1.profile): " << endl;
	string line;
	getline(cin, line);
	cout << endl;

	ifstream source(line, ios::binary);
	ofstream dest(line + ".bak", ios::binary);

	// file size
	source.seekg(0, ios::end);
	ifstream::pos_type size = source.tellg();
	source.seekg(0);
	// allocate memory for buffer
	char* buffer = new char[size];

	// copy file    
	source.read(buffer, size);
	dest.write(buffer, size);

	// clean up
	delete[] buffer;
	source.close();
	dest.close();

	return line;
}
