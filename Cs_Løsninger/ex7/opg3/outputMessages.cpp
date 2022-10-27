#include <outputMessages.hpp>
#include <iostream>

void DriveToEntryDoor(std::string* id)
{
    std::cout << "Look at me everybody. Im a " << *id << "! Im driving to the ENTRY door. Wrooom Wrooom." << std::endl << std::endl;
}

void DriveToExitDoor(std::string* id)
{
    std::cout << "Fuck this stupid parking lot! This " << *id << " is driving to the EXIT door! Wrooom." << std::endl << std::endl;
}

void ExitParkingLot(std::string* id)
{
    std::cout << *id << " LEAVING parking lot. Im back you 'outside' loosers!" << std::endl << std::endl;
}

void EnterParkingLot(std::string* id)
{
    std::cout << *id << " ENTERING parking lot.. See ya loosers!" << std::endl << std::endl;
}

void OpenEntryDoor(std::string* id)
{
    std::cout << "OPENING ENTRY door for " << *id << ". 'Wooosh'." << std::endl << std::endl;
}

void CloseEntryDoor(std::string* id)
{
    std::cout << "CLOSING ENTRY door for " << *id << ". 'Swoop'." << std::endl << std::endl;
}

void OpenExitDoor(std::string* id)
{
    std::cout << "OPENING EXIT door for " << *id << ". 'Wooosh'." << std::endl << std::endl;
}

void CloseExitDoor(std::string* id)
{
    std::cout << "CLOSING EXIT door for " << *id << ". Wooosh." << std::endl << std::endl;  
}