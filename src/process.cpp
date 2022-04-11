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

string statStrings[3] = { "Player Points",
    "Kills",
    "Deaths" };

void editmedals(string filename);
void editstats(string filename);


#define numberofbytesinfile 4356 // last offset 4356=0x1104
#define medalsstart 1404 // 0x57c
#define medalsend 1422 // 0x58d
#define statsstart 3980 // 0xf8c
#define statend 3992 // 0xf97
