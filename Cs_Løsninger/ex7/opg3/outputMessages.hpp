#ifndef OUTPUT_MESSAGES_HPP
#define OUTPUT_MESSAGES_HPP

#include <string>

void DriveToEntryDoor(std::string* id);
void DriveToExitDoor(std::string* id);
void ExitParkingLot(std::string* id);
void EnterParkingLot(std::string* id);
void OpenEntryDoor(std::string* id);
void CloseEntryDoor(std::string* id);
void OpenExitDoor(std::string* id);
void CloseExitDoor(std::string* id);


#endif