#include <iostream>
using namespace std;

bool entryDoorOpen = false;
bool exitDoorOpen = false;
bool carWaiting = false;


void DriveToEntryDoor()
{
    cout << "Im a little car. Im driving to the Entry door. Wrooom Wrooom." << endl;
    carWaiting = true;
}

void DriveToExitDoor()
{
    cout << "Fuck it. I'm leaving this place! Wrooom." << endl;
    carWaiting = true;
}

void ExitParkingLot()
{
    cout << "Leaving parking lot. Im back bitches!" << endl;
    carWaiting = false;
}

void EnterParkingLot()
{
    cout << "Entering parking lot.. SEE YA!" << endl; 
    carWaiting = false;
}

void ParkInside()
{
    cout << "I'm parking my booty right here." << endl << endl;
    sleep(1);
}

void WaitOutside()
{
    cout << "I'm waiting outside.. boohooo! (sad smileyface)" << endl << endl;
    sleep(1);
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
    cout << "Closing EXIT door. 'Swoop'." << endl;
    exitDoorOpen = false;
}
