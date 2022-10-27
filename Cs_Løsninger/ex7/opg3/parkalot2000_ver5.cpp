#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/ThreadError.hpp>
#include <osapi/Utility.hpp>
#include <osapi/Conditional.hpp>
#include <iostream>
#include <EntryGuardThread.hpp>
#include <ExitGuardThread.hpp>
#include <CarThread.hpp>
#include <messages.hpp>
#include <string>

int main()                                                              //Program
{
    std::string carTypes[NO_OF_CARS] = {"Kia", "Volvo", "Tesla", "Renault", "Mercedes Benz", 
                                  "BMW", "Audi", "Suzuki", "Skoda", "Ford"};

    EntryGuardThread entryGuard;
    ExitGuardThread exitGuard;
    CarThread* car[NO_OF_CARS];
    osapi::Thread* carthreads[NO_OF_CARS];

    osapi::Thread entrythread(&entryGuard);
    entrythread.start();
    osapi::Thread exitthread(&exitGuard);
    exitthread.start();

    for (int i = 0; i < NO_OF_CARS; i++)                                // Create/init car threads. 
    {
        startInd* start = new startInd;
        start->greenLight = true;
        car[i] = new CarThread{&carTypes[i], entryGuard.getMsgQueue(), exitGuard.getMsgQueue()};

        car[i]->getMsgQueue()->send(ID_START_IND, start);

        carthreads[i] = new osapi::Thread{car[i]};
        
        carthreads[i]->start();

        osapi::sleep(1000);
    }
    
    for (int i = 0; i < NO_OF_CARS; i++)                            
    {
        carthreads[i]->join();
    }

    entrythread.join();
    exitthread.join();

    return 0;
}
