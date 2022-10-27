#include <iostream>
#include <string>
using namespace std;


bool entryDoorOpen = false;
bool exitDoorOpen = false;
bool carWaitingByEntry = false;
bool carWaitingByExit = false;
bool entryOccupied = false;
bool exitOccupied = false;

void DriveToEntryDoor(string* id)
{
    entryOccupied = true;
    cout << "Look at me everybody. Im a " << *id << "! Im driving to the ENTRY door. Wrooom Wrooom." << endl;
    carWaitingByEntry = true;
}

void DriveToExitDoor(string *id)
{
    exitOccupied = true;
    cout << "Fuck this stupid parking lot! This " << *id << " is driving to the EXIT door! Wrooom." << endl;
    carWaitingByExit = true;
}

void ExitParkingLot(string *id)
{
    cout << *id << " LEAVING parking lot. Im back you 'outside' loosers!" << endl;
    carWaitingByExit = false;
}

void EnterParkingLot(string *id)
{
    cout << *id << " ENTERING parking lot.. See ya loosers!" << endl;
    carWaitingByEntry = false;
}

void ParkInside(string *id)
{
    cout << *id << " is PARKING its booty right here in the parking lot." << endl << endl;
    entryOccupied = false;
}

void WaitOutside(string *id)
{
    cout << *id << " is WAITING OUTSIDE.. boohooo! (sad smileyface)" << endl << endl;
    exitOccupied = false;
}

void OpenEntryDoor()
{
    cout << "Openingen ENTRY door. 'Wooosh'." << endl;
    entryDoorOpen = true;
}

void CloseEntryDoor()
{
    cout << "Closing ENTRY door. 'Swoop'." << endl;
    entryDoorOpen = false;
}

void OpenExitDoor()
{
    cout << "Openingen EXIT door. 'Wooosh'." << endl;
    exitDoorOpen = true;
}

void CloseExitDoor()
{
    cout << "Closing EXIT door. 'Wooosh'." << endl;
    exitDoorOpen = false;
}
