#include <EntryGuardThread.hpp>

EntryGuardThread::EntryGuardThread() 
    :   mq_(QUEUE_SIZE), running_(true)
{}

osapi::MsgQueue* EntryGuardThread::getMsgQueue() 
{
    return &mq_;
}

void EntryGuardThread::run()
{
    while(running_)
    {
        unsigned long id;
        osapi::Message* msg = mq_.receive(id);    // receive message and id
        handleMsg(id, msg);              // pass message to message handler
        delete(msg); 
    }
    return;
}

void EntryGuardThread::handleMsg(unsigned long id, osapi::Message* msg)    //Entry guard Dispatcher (Handle switch)
{                                                                //static cast to convert Message pointer to inheritance type
    switch (id)
    {
        case ID_ENTRY_DOOR_OPEN_REQ:
        handleReq(static_cast<entryDoorOpenReq*>(msg));
        break;

        case ID_CAR_THROUGH_IND:
        handleInd(static_cast<carPassedEntryDoorInd*>(msg));
        break;
    
        default:
        break;
    }
}

void EntryGuardThread::handleReq(entryDoorOpenReq* req)                  //Handler for ID_ENTRY_DOOR_OPEN_REQ
{
    OpenEntryDoor(req->name);                                     //Udskrift metode. output to stdout
    entryDoorOpenCfm* cfm = new entryDoorOpenCfm;                 //Opret dynamisk ny message objekt pointer                   
    cfm->entryDoorOpen = true;                                    // message objektets attribut sættes. indicate that door is open          
    req->whoIsAsking->send(ID_ENTRY_DOOR_OPEN_CFM, cfm);          // send confirm message to car queue
}

void EntryGuardThread::handleInd(carPassedEntryDoorInd* ind)              //Handler for ID_CAR_THROUGH_IND
{
    if(ind->carPassedEntry)
    {                                       //Hvis bilen/tråden er kørt ind
        CloseEntryDoor(ind->name);

        if(++countCars_ == NO_OF_CARS)
            running_ = false;
    }                                //Udskrift metode. Døren lukket for tråd/bil navn: xx
}