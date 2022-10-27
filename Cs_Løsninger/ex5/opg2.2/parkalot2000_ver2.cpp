#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "functions.h"

pthread_mutex_t entry_mutex;
pthread_mutex_t exit_mutex;
pthread_mutex_t entry_occupied_mutex;
pthread_mutex_t exit_occupied_mutex;
pthread_cond_t entry_signal;
pthread_cond_t exit_signal;
pthread_cond_t entry_occupied_signal;
pthread_cond_t exit_occupied_signal;


void *car_function(void *d)
{
    string* id = (string*) d;
    for(;;)
    {
        /* Enter garage and park */
        
        pthread_mutex_lock(&entry_mutex);     // lock mutex

        while(entryOccupied)                  // wait if occupied by another car
            pthread_cond_wait(&entry_occupied_signal, 
                              &entry_mutex); 
        DriveToEntryDoor(id);                 // drive to entry door
        pthread_cond_signal(&entry_signal);   // signal to entry guard that car is waiting

        while(!entryDoorOpen)                 // wait untill entry guard signals that garage door is open
            pthread_cond_wait(&entry_signal, 
                              &entry_mutex); 
        EnterParkingLot(id);                    // enter parking lot
        pthread_cond_signal(&entry_signal);   // signal to entry guard that car is no longer waiting

        while(entryDoorOpen)                  // wait untill entry guard signals that garage door is closed
            pthread_cond_wait(&entry_signal, 
                              &entry_mutex); 
        ParkInside(id);                         // park inside parking lot and wait
        pthread_cond_broadcast(&entry_occupied_signal);
        pthread_mutex_unlock(&entry_mutex);   // unlock mutex
        sleep(rand() % 5 + 1);


        /* Exit garage and wait outside*/
        
        pthread_mutex_lock(&exit_mutex);      // lock mutex
        while(exitOccupied)                   // wait if occupied by another car
            pthread_cond_wait(&exit_occupied_signal, 
                              &exit_mutex);             
        DriveToExitDoor(id);                  // drive to exit door
        pthread_cond_signal(&exit_signal);    // signal to exit guard that car is waiting

        while(!exitDoorOpen)                  // wait untill exit guard signals that garage door is open
            pthread_cond_wait(&exit_signal, 
                              &exit_mutex); 
        ExitParkingLot(id);                     // exit parking lot
        pthread_cond_signal(&exit_signal);    // signal to exit guard that car is no longer waiting

        while(exitDoorOpen)                   // wait untill exit guard signals that garage door is closed
            pthread_cond_wait(&exit_signal,
                              &exit_mutex); 
        WaitOutside(id);                        // wait outside parking lot
        pthread_cond_broadcast(&exit_occupied_signal); // signal that exit is not occupied any more
        pthread_mutex_unlock(&exit_mutex);    // unlock mutex
        sleep(rand() % 5 + 1);
    }

    pthread_exit(NULL);
}

void *EntryGuard_function(void *d)
{
    for(;;)
    {
        pthread_mutex_lock(&entry_mutex);        // lock mutex

        while(!carWaitingByEntry)                // wait untill a car signals that it is waiting by the door
            pthread_cond_wait(&entry_signal, 
                              &entry_mutex);
        OpenEntryDoor();                         // open entry door
        pthread_cond_broadcast(&entry_signal);   // signal to car that entry door is open

        while(carWaitingByEntry)                 // wait untill car signals that it has entered
            pthread_cond_wait(&entry_signal, 
                              &entry_mutex);
        CloseEntryDoor();                        // close entry door
        pthread_cond_broadcast(&entry_signal);   // signal to car that entry door is closed
        pthread_mutex_unlock(&entry_mutex);      // unlock mutex
    }

    pthread_exit(NULL);
}

void *ExitGuard_function(void *d)
{
    for(;;)
    {
        pthread_mutex_lock(&exit_mutex);         // lock mutex

        while(!carWaitingByExit)                 // wait untill a car signals that it is waiting by the door
            pthread_cond_wait(&exit_signal, 
                              &exit_mutex);
        OpenExitDoor();                          // open exit door
        pthread_cond_broadcast(&exit_signal);    // signal to car that garage door is open

        while(carWaitingByExit)                  // wait untill car has exited
            pthread_cond_wait(&exit_signal, 
                              &exit_mutex);
        CloseExitDoor();                         // close exit door
        pthread_cond_broadcast(&exit_signal);    // signal to car that exit door is closed
        pthread_mutex_unlock(&exit_mutex);       // unlock mutex
    }
    
    pthread_exit(NULL);
}

int main()
{
    srand (time(NULL));
    const int NO_OF_CARS = 10;

    pthread_t entryGuard;
    pthread_t exitGuard;
    pthread_t cars[NO_OF_CARS];
    string id[NO_OF_CARS] = {"Kia", "Volvo", "Tesla", "Renault", "Mercedes Benz", 
                                  "BMW", "Audi", "Suzuki", "Skoda", "Ford"};

    pthread_mutex_init(&entry_mutex, NULL);
    pthread_mutex_init(&exit_mutex, NULL);
    pthread_cond_init(&entry_signal, NULL);
    pthread_cond_init(&exit_signal, NULL);
    
    for (int i = 0; i < NO_OF_CARS; i++)
    {
        pthread_create(&cars[i], nullptr, car_function, static_cast <void*>(&id[i]));
    }

    pthread_create(&entryGuard, nullptr, EntryGuard_function, nullptr);
    pthread_create(&exitGuard, nullptr, ExitGuard_function, nullptr);

    for (int i = 0; i < NO_OF_CARS; i++)
    {
        pthread_join(cars[i], NULL);
    }

    pthread_join(entryGuard, NULL);
    pthread_join(exitGuard, NULL);
    
    return 0;
}
