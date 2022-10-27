#include <ExitGuardThread.hpp>

ExitGuardThread::ExitGuardThread() 
    :   mq_(QUEUE_SIZE), running_(true)
{}

osapi::MsgQueue* ExitGuardThread::getMsgQueue() 
{
    return &mq_;
}

void ExitGuardThread::run()
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

void ExitGuardThread::handleMsg(unsigned long id, osapi::Message* msg)    //Entry guard Dispatcher (Handle switch)
{                                                                //static cast to convert Message pointer to inheritance type
    switch (id)
    {
        case ID_EXIT_DOOR_OPEN_REQ:
        handleReq(static_cast<exitDoorOpenReq*>(msg));
        break;

        case ID_CAR_THROUGH_IND:
        handleInd(static_cast<carPassedExitDoorInd*>(msg));
        break;
    
        default:
        break;
    }
}

void ExitGuardThread::handleReq(exitDoorOpenReq* req)                    //Handler for ID_EXIT_DOOR_OPEN_REQ
{
    OpenExitDoor(req->name);                                     //Udskrift metode. Navn på tråd/bil der kører ud af exit guard. 
    exitDoorOpenCfm* cfm = new exitDoorOpenCfm;                  //Opretter ny dynamisk message pointer
    cfm->exitDoorOpen = true;                                    // sætter objekts attribut =true. Exit door er åben. 
    req->whoIsAsking->send(ID_EXIT_DOOR_OPEN_CFM, cfm);          //send confirm message to exitguard queue.
}

void ExitGuardThread::handleInd(carPassedExitDoorInd* ind)              //Handler for ID_CAR_THROUGH_IND
{
    if(ind->carPassedExit)
    {                                      //Hvis bilen er kørt ud. Udskriv med tråd navn.                             
        CloseExitDoor(ind->name);

        if(++countCars_ == NO_OF_CARS)
            running_ = false;
    }
    
}