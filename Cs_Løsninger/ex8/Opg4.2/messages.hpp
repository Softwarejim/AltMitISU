#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include <osapi/Message.hpp>
#include <osapi/MsgQueue.hpp>
#include <string>
const int NO_OF_CARS = 10;

/************* IDs (Used messages) ***********/

enum
{
    ID_START_IND,
    ID_START_OUT,
    ID_ENTRY_DOOR_OPEN_CFM,
    ID_EXIT_DOOR_OPEN_CFM,
    ID_ENTRY_DOOR_OPEN_REQ,
    ID_EXIT_DOOR_OPEN_REQ,
    ID_CAR_THROUGH_IND
};

/************* Messages (Used for each car object) ***********/

struct startInd : public osapi::Message          
{
    bool greenLight = false;
};

struct exitInd : public osapi::Message 
{
    bool greenLight = false;
};

struct entryDoorOpenReq : public osapi::Message 
{
    osapi::MsgQueue* whoIsAsking = nullptr;
    std::string* name = nullptr;
};

struct exitDoorOpenReq : public osapi::Message 
{
    osapi::MsgQueue* whoIsAsking = nullptr;
    std::string* name = nullptr;
};

struct entryDoorOpenCfm : public osapi::Message 
{
    bool entryDoorOpen = false;
};

struct exitDoorOpenCfm : public osapi::Message 
{
    bool exitDoorOpen = false;
};

struct carPassedEntryDoorInd : public osapi::Message 
{
    osapi::MsgQueue* whoIsTelling = nullptr;
    std::string* name = nullptr;
    bool carPassedEntry = false;
};

struct carPassedExitDoorInd : public osapi::Message 
{
    osapi::MsgQueue* whoIsTelling = nullptr;
    std::string* name = nullptr;
    bool carPassedExit = false;
};


#endif