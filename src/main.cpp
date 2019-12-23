/*
*****************************************************************************

  File        : main.cpp

  See LICENSE for code licensing.

*****************************************************************************
*/

#include<iostream>
#include<cstdint>
#include<fstream>
#include<string>

using namespace std;

void editmedals(void);
void editstats(void);

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

	cout << "Hello World!" << endl;

	uint8_t c = ' '; // command
	bool exit = false;

	do
	{
		cout << endl;
		cout << "Star Wars Battlefront II Classic Profile Editor. Select a fleet to Command: " << endl;
		cout << "m: edit medals | s: edit stats | e: exit" << endl;
		cout << "Enter command: ";
		getline(cin, c);
		cout << endl;

		switch (c) {
		case 'm':
		{
			editmedals();
		}
			break;
		case 's':
		{
			editstats();
		}
			break;
		case 'e':
		{
			exit = true;
		}
		break;
		}

	} while (!exit);

	system("cls");
	//printStruct();

	return 0;
}

void editmedals(void){
	string filename;
	filename = backupfile();


}

void editstats(void){
	string filename;
	filename = backupfile();
}

string backupfile(void){

	cout << "Enter filename only: " << endl;
	string line;
	getline(cin, line);
	cout << endl;

	ifstream src(line, ios::binary);
	ofstream dst(line + ".bak",   ios::binary);

	dst << src.rdbuf();

	return line;
}
