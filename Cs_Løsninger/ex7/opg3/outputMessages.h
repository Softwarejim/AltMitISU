#ifndef OUTPUT_MESSAGES_HPP
#define OUTPUT_MESSAGES_HPP

#include <iostream>
#include <string>
using namespace std;

void DriveToEntryDoor(string* id)
{
    cout << "Look at me everybody. Im a " << *id << "! Im driving to the ENTRY door. Wrooom Wrooom." << endl << endl;
}

void DriveToExitDoor(string* id)
{
    cout << "Fuck this stupid parking lot! This " << *id << " is driving to the EXIT door! Wrooom." << endl << endl;
}

void ExitParkingLot(string* id)
{
    cout << *id << " LEAVING parking lot. Im back you 'outside' loosers!" << endl << endl;
}

void EnterParkingLot(string* id)
{
    cout << *id << " ENTERING parking lot.. See ya loosers!" << endl << endl;
}

void OpenEntryDoor(string* id)
{
    cout << "OPENING ENTRY door for " << *id << ". 'Wooosh'." << endl << endl;
}

void CloseEntryDoor(string* id)
{
    cout << "CLOSING ENTRY door for " << *id << ". 'Swoop'." << endl << endl;
}

void OpenExitDoor(string* id)
{
    cout << "OPENING EXIT door for " << *id << ". 'Wooosh'." << endl << endl;
}

void CloseExitDoor(string* id)
{
    cout << "CLOSING EXIT door for " << *id << ". Wooosh." << endl << endl;  
}

#endif