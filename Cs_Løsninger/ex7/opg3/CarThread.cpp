#include <CarThread.hpp>

CarThread::CarThread(std::string* name, osapi::MsgQueue* entryGuardQueue, osapi::MsgQueue* exitGuardQueue)
:   entryGuardMq_(entryGuardQueue), exitGuardMq_(exitGuardQueue), name_(*name), running_(true), mq_(QUEUE_SIZE)
{}

osapi::MsgQueue* CarThread::getMsgQueue() 
{ 
    return &mq_;
}

void CarThread::run()
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

void CarThread::handleMsg(unsigned long id, osapi::Message* msg)  //Car message Dispatcher (Handle switch)
{                                                                 //static cast to convert Message pointer to inheritance type
    switch (id)
    {
        case ID_START_IND:
        carHandleStartInd(static_cast<startInd*>(msg));
        break;
    
        case ID_ENTRY_DOOR_OPEN_CFM:
        carHandleEntryDoorOpenCfm(static_cast<entryDoorOpenCfm*>(msg));
        break;

        case ID_EXIT_DOOR_OPEN_CFM:
        carHandleExitDoorOpenCfm(static_cast<exitDoorOpenCfm*>(msg));
        break;

        case ID_START_OUT:
        carDriveOutInd(static_cast<exitInd*>(msg));
        break;

        default:
        break;
    }
}

void CarThread::carHandleStartInd(startInd* ind)                 //Handler for ID_START_IND
{
    if(ind->greenLight)                                          //Hvis der er grønt lys -> Kør ind
    {
        DriveToEntryDoor(&name_);                            //Udskrift metode. output to stdout
        entryDoorOpenReq* req = new entryDoorOpenReq;            //Opret dynamisk ny message objekt pointer
        req->whoIsAsking = &mq_;                             //message objektets MsgQueue pointer sættes til bilen/tråden queue.    
        req->name = &name_;                                  //message objektets name attribut sættes til bilens/trådens navn. 
        entryGuardMq_->send(ID_ENTRY_DOOR_OPEN_REQ, req);     //send req message to entry door queue
    }
}

void CarThread::carHandleEntryDoorOpenCfm(entryDoorOpenCfm* cfm)   //Handler for ID_ENTRY_DOOR_OPEN_CFM
{
    if(cfm->entryDoorOpen)                                        //Hvis message objektets attribut er true (persmission to enter)
    {
        EnterParkingLot(&name_);                              //Udskrift metode med bilen/trådens navn. 
        carPassedEntryDoorInd* ind1 = new carPassedEntryDoorInd;  //Opret dynamisk ny message objekt pointer 
        ind1->carPassedEntry = true;                              //Registrer at bilen/tråden er kørt ind. 
        ind1->whoIsTelling = &mq_;                            //Objektets MsgQueue pointer sættes til bilens/trådens MsgQueue
        ind1->name = &name_;                                  //message objektet's name attribut sættes til bilens/trådens navn. 
        entryGuardMq_->send(ID_CAR_THROUGH_IND, ind1);         //send ind1 message to entry guard queue. Message sent that car has driven through
    
        osapi::sleep(1000);                                                 //Sleep 1 sec.

        exitInd* ind2 = new exitInd;                              //Opretter ny dynamisk message pointer
        ind2->greenLight = true;                                  //Sætter objektets attribut til true
        mq_.send(ID_START_OUT, ind2);                         //send ind2 message to car queue. Message sent car to it self that it should leave again. 
    }
}


void CarThread::carDriveOutInd(exitInd* ind)                       //Handler for ID_START_OUT
{
    if(ind->greenLight)                                           //Hvis der gives grønt lys til at køre ud. 
    {
        DriveToExitDoor(&name_);                              //Udskrift metode med tråd/bil navn.
        exitDoorOpenReq* req = new exitDoorOpenReq;               //Opretter ny dynamisk message pointer
        req->whoIsAsking = &mq_;                              //message objektets MsgQueue pointer sættes til bilen/tråden queue. 
        req->name = &name_;                                   //message objektets name attribut sættes til bilens/trådens navn. 
        exitGuardMq_->send(ID_EXIT_DOOR_OPEN_REQ, req);        // send req message to exitguard queue
    }
}


void CarThread::carHandleExitDoorOpenCfm(exitDoorOpenCfm* cfm)    //Handler for ID_EXIT_DOOR_OPEN_CFM
{
    if(cfm->exitDoorOpen)                                        //Hvis confirm message == true
    {
        ExitParkingLot(&name_);                              //Udskrift metode med tråd/bil navn
        carPassedExitDoorInd* ind = new carPassedExitDoorInd;    //Opretter ny dynamisk message pointer
        ind->carPassedExit = true;                               //Sætter attribut. Bilen/tråden er kørt forbi exitguard. 
        ind->whoIsTelling = &mq_;                            //Objektets MsgQueue pointer sættes til bilens/trådens MsgQueue
        ind->name = &name_;                                  //message objektet's name attribut sættes til bilens/trådens navn. 
        exitGuardMq_->send(ID_CAR_THROUGH_IND, ind);          //send ind message to exit guard queue. Message sent that car has driven through

        running_ = false;
    }
}