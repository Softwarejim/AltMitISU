#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "outputMessages.h"
#include "MsgQueue.h"
const int NO_OF_CARS = 10;
const unsigned long MAX_SIZE = 20;

MsgQueue entryGateMQ_(MAX_SIZE);                //Message queue til entryguard
MsgQueue exitGateMQ_(MAX_SIZE);                 //Message queue til exit guard

/******* Senders / receivers (objects containing data) *******/

struct Car
{
    MsgQueue MQ{MAX_SIZE};
    MsgQueue* entryGateMQ = nullptr;
    MsgQueue* exitGateMQ = nullptr;
    string name;
    pthread_t thread;
};

struct entryGuard
{
    MsgQueue* MQ = &entryGateMQ_;
    pthread_t thread;
};

struct exitGuard
{
    MsgQueue* MQ = &exitGateMQ_;
    pthread_t thread;
};

/************* Messages (Used for each car object) ***********/

struct startInd : public Message            
{
    bool greenLight = false;
};

struct exitInd : public Message
{
    bool greenLight = false;
};

struct entryDoorOpenReq : public Message
{
    MsgQueue* whoIsAsking = nullptr;
    string* name = nullptr;
};

struct exitDoorOpenReq : public Message
{
    MsgQueue* whoIsAsking = nullptr;
    string* name = nullptr;
};

struct entryDoorOpenCfm : public Message
{
    bool entryDoorOpen = false;
};

struct exitDoorOpenCfm : public Message
{
    bool exitDoorOpen = false;
};

struct carPassedEntryDoorInd : public Message
{
    MsgQueue* whoIsTelling = nullptr;
    string* name = nullptr;
    bool carPassedEntry = false;
};

struct carPassedExitDoorInd : public Message
{
    MsgQueue* whoIsTelling = nullptr;
    string* name = nullptr;
    bool carPassedExit = false;
};

/******* ID Tags *******/               //Used in dispatcher switches  (Message handlers)

enum : unsigned long
{
    ID_START_IND,
    ID_START_OUT,
    ID_ENTRY_DOOR_OPEN_CFM,
    ID_EXIT_DOOR_OPEN_CFM,
    ID_ENTRY_DOOR_OPEN_REQ,
    ID_EXIT_DOOR_OPEN_REQ,
    ID_CAR_THROUGH_IND
};

void carHandleStartInd(Car* car, startInd* ind)                 //Handler for ID_START_IND
{
    if(ind->greenLight)                                          //Hvis der er grønt lys -> Kør ind
    {
        DriveToEntryDoor(&car->name);                            //Udskrift metode. output to stdout
        entryDoorOpenReq* req = new entryDoorOpenReq;            //Opret dynamisk ny message objekt pointer
        req->whoIsAsking = &car->MQ;                             //message objektets MsgQueue pointer sættes til bilen/tråden queue.    
        req->name = &car->name;                                  //message objektets name attribut sættes til bilens/trådens navn. 
        car->entryGateMQ->send(ID_ENTRY_DOOR_OPEN_REQ, req);     //send req message to entry door queue
    }
}

void entryGuardHandleReq(entryDoorOpenReq* req)                  //Handler for ID_ENTRY_DOOR_OPEN_REQ
{
    OpenEntryDoor(req->name);                                     //Udskrift metode. output to stdout
    entryDoorOpenCfm* cfm = new entryDoorOpenCfm;                 //Opret dynamisk ny message objekt pointer                   
    cfm->entryDoorOpen = true;                                    // message objektets attribut sættes. indicate that door is open          
    req->whoIsAsking->send(ID_ENTRY_DOOR_OPEN_CFM, cfm);          // send confirm message to car queue
}

void carHandleEntryDoorOpenCfm(Car* car, entryDoorOpenCfm* cfm)   //Handler for ID_ENTRY_DOOR_OPEN_CFM
{
    if(cfm->entryDoorOpen)                                        //Hvis message objektets attribut er true (persmission to enter)
    {
        EnterParkingLot(&car->name);                              //Udskrift metode med bilen/trådens navn. 
        carPassedEntryDoorInd* ind1 = new carPassedEntryDoorInd;  //Opret dynamisk ny message objekt pointer 
        ind1->carPassedEntry = true;                              //Registrer at bilen/tråden er kørt ind. 
        ind1->whoIsTelling = &car->MQ;                            //Objektets MsgQueue pointer sættes til bilens/trådens MsgQueue
        ind1->name = &car->name;                                  //message objektet's name attribut sættes til bilens/trådens navn. 
        car->entryGateMQ->send(ID_CAR_THROUGH_IND, ind1);         //send ind1 message to entry guard queue. Message sent that car has driven through
    
        sleep(1);                                                 //Sleep 1 sec.

        exitInd* ind2 = new exitInd;                              //Opretter ny dynamisk message pointer
        ind2->greenLight = true;                                  //Sætter objektets attribut til true
        car->MQ.send(ID_START_OUT, ind2);                         //send ind2 message to car queue. Message sent car to it self that it should leave again. 
    }
}

void entryGuardHandleInd(carPassedEntryDoorInd* ind)              //Handler for ID_CAR_THROUGH_IND
{
    if(ind->carPassedEntry)                                       //Hvis bilen/tråden er kørt ind
        CloseEntryDoor(ind->name);                                //Udskrift metode. Døren lukket for tråd/bil navn: xx
}

void carDriveOutInd(Car* car, exitInd* ind)                       //Handler for ID_START_OUT
{
    if(ind->greenLight)                                           //Hvis der gives grønt lys til at køre ud. 
    {
        DriveToExitDoor(&car->name);                              //Udskrift metode med tråd/bil navn.
        exitDoorOpenReq* req = new exitDoorOpenReq;               //Opretter ny dynamisk message pointer
        req->whoIsAsking = &car->MQ;                              //message objektets MsgQueue pointer sættes til bilen/tråden queue. 
        req->name = &car->name;                                   //message objektets name attribut sættes til bilens/trådens navn. 
        car->exitGateMQ->send(ID_EXIT_DOOR_OPEN_REQ, req);        // send req message to exitguard queue
    }
}

void exitGuardHandleReq(exitDoorOpenReq* req)                    //Handler for ID_EXIT_DOOR_OPEN_REQ
{
    OpenExitDoor(req->name);                                     //Udskrift metode. Navn på tråd/bil der kører ud af exit guard. 
    exitDoorOpenCfm* cfm = new exitDoorOpenCfm;                  //Opretter ny dynamisk message pointer
    cfm->exitDoorOpen = true;                                    // sætter objekts attribut =true. Exit door er åben. 
    req->whoIsAsking->send(ID_EXIT_DOOR_OPEN_CFM, cfm);          //send confirm message to exitguard queue.
}

void carHandleExitDoorOpenCfm(Car* car, exitDoorOpenCfm* cfm)    //Handler for ID_EXIT_DOOR_OPEN_CFM
{
    if(cfm->exitDoorOpen)                                        //Hvis confirm message == true
    {
        ExitParkingLot(&car->name);                              //Udskrift metode med tråd/bil navn
        carPassedExitDoorInd* ind = new carPassedExitDoorInd;    //Opretter ny dynamisk message pointer
        ind->carPassedExit = true;                               //Sætter attribut. Bilen/tråden er kørt forbi exitguard. 
        ind->whoIsTelling = &car->MQ;                            //Objektets MsgQueue pointer sættes til bilens/trådens MsgQueue
        ind->name = &car->name;                                  //message objektet's name attribut sættes til bilens/trådens navn. 
        car->exitGateMQ->send(ID_CAR_THROUGH_IND, ind);          //send ind message to exit guard queue. Message sent that car has driven through
    }
}

void exitGuardHandleInd(carPassedExitDoorInd* ind)              //Handler for ID_CAR_THROUGH_IND
{
    if(ind->carPassedExit)                                      //Hvis bilen er kørt ud. Udskriv med tråd navn.                             
        CloseExitDoor(ind->name);
    
}

void carMessageHandler(Car* car, unsigned long id, Message* msg)  //Car message Dispatcher (Handle switch)
{                                                                 //static cast to convert Message pointer to inheritance type
    switch (id)
    {
        case ID_START_IND:
        carHandleStartInd(car, static_cast<startInd*>(msg));
        break;
    
        case ID_ENTRY_DOOR_OPEN_CFM:
        carHandleEntryDoorOpenCfm(car, static_cast<entryDoorOpenCfm*>(msg));
        break;

        case ID_EXIT_DOOR_OPEN_CFM:
        carHandleExitDoorOpenCfm(car, static_cast<exitDoorOpenCfm*>(msg));
        break;

        case ID_START_OUT:
        carDriveOutInd(car, static_cast<exitInd*>(msg));
        break;

        default:
        break;
    }
}

void entryGuardMessageHandler(unsigned long id, Message* msg)    //Entry guard Dispatcher (Handle switch)
{                                                                //static cast to convert Message pointer to inheritance type
    switch (id)
    {
        case ID_ENTRY_DOOR_OPEN_REQ:
        entryGuardHandleReq(static_cast<entryDoorOpenReq*>(msg));
        break;

        case ID_CAR_THROUGH_IND:
        entryGuardHandleInd(static_cast<carPassedEntryDoorInd*>(msg));
        break;
    
        default:
        break;
    }
}

void exitGuardMessageHandler(unsigned long id, Message* msg)     //Exit guard Dispatcher (Handle switch)
{                                                                //static cast to convert Message pointer to inheritance type
    switch (id)
    {
    case ID_EXIT_DOOR_OPEN_REQ:
    exitGuardHandleReq(static_cast<exitDoorOpenReq*>(msg));
    break;

    case ID_CAR_THROUGH_IND:
    exitGuardHandleInd(static_cast<carPassedExitDoorInd*>(msg));
    break;
    
    default:
    break;
    }

}

void* carThreads(void *d)                                       //Thread func.
{
    Car* car = static_cast<Car*>(d);

    for(;;)
    {
        unsigned long id;       
        Message* msg = car->MQ.receive(id);          // receive message and id
        carMessageHandler(car, id, msg);             // pass message to message handler
        delete(msg);                                 // delete message
    }

    pthread_exit(NULL);
}

Car* initCar(string name, MsgQueue* entryGateMQ, MsgQueue* exitGateMQ)  //Car objekt init
{
    Car* car = new Car;                                                //Initier attributter ved nyt dynamisk car pointer
    car->name = name;
    car->entryGateMQ = entryGateMQ;
    car->exitGateMQ = exitGateMQ;

    pthread_create(&car->thread, nullptr, carThreads, car);            //opret tråd.

    return car;
}

void* entryGuardThread(void *d)                                         //Entry guard thread func
{
    entryGuard* entryGuard_ = static_cast<entryGuard*>(d);

    for(;;)
    {
        unsigned long id;
        Message* msg = entryGuard_->MQ->receive(id);  // receive message and id
        entryGuardMessageHandler(id, msg);            // pass message to message handler
        delete(msg);                                  // delete message
    }

    pthread_exit(NULL);
}

void* exitGuardThread(void *d)                                         //Exit guard thread func
{
    exitGuard* exitGuard_ = static_cast<exitGuard*>(d);

    for(;;)
    {
        unsigned long id;
        Message* msg = exitGuard_->MQ->receive(id);    // receive message and id
        exitGuardMessageHandler(id, msg);              // pass message to message handler
        delete(msg);                                   // delete message
    }
    
    pthread_exit(NULL);
}

void cleanUp(Car* cars, pthread_t* entry, pthread_t* exit)              //Clean up func
{
    for (int i = 0; i < NO_OF_CARS; i++)
    {
        pthread_join(cars[i].thread, NULL);
    }
    
    cars = nullptr;

    pthread_join(*entry, NULL);
    pthread_join(*exit, NULL);
}

int main()                                                              //Program
{   
    string carTypes[NO_OF_CARS] = {"Kia", "Volvo", "Tesla", "Renault", "Mercedes Benz", 
                                  "BMW", "Audi", "Suzuki", "Skoda", "Ford"};

    pthread_t entryGuardThread_;                                        // Define entry/exit guard threads
    pthread_t exitGuardThread_;

    entryGuard entryGuard_;                                             //Define entry/exit guard objekts including pointer to queue and a thread. 
    exitGuard exitGuard_ ;

    Car* cars[NO_OF_CARS];                                              //Car array pointer

    pthread_create(&entryGuardThread_, nullptr, entryGuardThread, static_cast<void*>(&entryGuard_));  //Create entry/exit guard threads. 
    pthread_create(&exitGuardThread_, nullptr, exitGuardThread, static_cast<void*>(&exitGuard_));

    for (int i = 0; i < NO_OF_CARS; i++)                                // Create/init car threads. 
    {
        startInd* start = new startInd;
        start->greenLight = true;
        cars[i] = initCar(carTypes[i], &entryGateMQ_, &exitGateMQ_);
        cars[i]->MQ.send(ID_START_IND, start);
        sleep(1);
    }
    
    cleanUp(*cars, &entryGuardThread_, &exitGuardThread_);              //Clean up threads.

    return 0;
}
