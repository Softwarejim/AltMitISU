#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "functions.h"

pthread_mutex_t entry_mutex;
pthread_mutex_t exit_mutex;
pthread_cond_t entry_signal;
pthread_cond_t exit_signal;

pthread_t car;
pthread_t entryGuard;
pthread_t exitGuard;

void *car_function(void *d)
{
    for(;;)
    {
        /* Enter garage and park */

        pthread_mutex_lock(&entry_mutex);     // lock mutex
        DriveToEntryDoor();                   // drive to entry door
        pthread_cond_signal(&entry_signal);   // signal to entry guard that car is waiting

        while(!entryDoorOpen)                 // wait untill entry guard signals that garage door is open
            pthread_cond_wait(&entry_signal, 
                              &entry_mutex); 
        EnterParkingLot();                    // enter parking lot
        pthread_cond_signal(&entry_signal);   // signal to entry guard that car is no longer waiting

        while(entryDoorOpen)                  // wait untill entry guard signals that garage door is closed
            pthread_cond_wait(&entry_signal, 
                              &entry_mutex); 
        
        pthread_mutex_unlock(&entry_mutex);   // unlock mutex
        ParkInside();                         // park inside parking lot and wait


        /* Exit garage and wait outside*/

        pthread_mutex_lock(&exit_mutex);      // lock mutex
        DriveToExitDoor();                    // drive to exit door
        pthread_cond_signal(&exit_signal);    // signal to exit guard that car is waiting

        while(!exitDoorOpen)                  // wait untill exit guard signals that garage door is open
            pthread_cond_wait(&exit_signal, 
                              &exit_mutex); 
        ExitParkingLot();                     // exit parking lot
        pthread_cond_signal(&exit_signal);   // signal to exit guard that car is no longer waiting

        while(exitDoorOpen)                   // wait untill exit guard signals that garage door is closed
            pthread_cond_wait(&exit_signal,
                              &exit_mutex); 
        
        pthread_mutex_unlock(&exit_mutex);    // unlock mutex
        WaitOutside();                        // wait outside parking lot
    }

    pthread_exit(NULL);
}

void *EntryGuard_function(void *d)
{
    for(;;)
    {
        pthread_mutex_lock(&entry_mutex);     // lock mutex

        while(!carWaiting)                    // wait untill a car signals that it is waiting by the door
            pthread_cond_wait(&entry_signal, 
                              &entry_mutex);
        OpenEntryDoor();                      // open entry door
        pthread_cond_signal(&entry_signal);   // signal to car that entry door is open

        while(carWaiting)                     // wait untill car signals that it has entered
            pthread_cond_wait(&entry_signal, 
                              &entry_mutex);
        CloseEntryDoor();                     // close entry door
        pthread_cond_signal(&entry_signal);   // signal to car that entry door is closed
        pthread_mutex_unlock(&entry_mutex);   // unlock mutex
    }

    pthread_exit(NULL);
}

void *ExitGuard_function(void *d)
{
    for(;;)
    {
        pthread_mutex_lock(&exit_mutex);      // lock mutex

        while(!carWaiting)                    // wait untill a car signals that it is waiting by the door
            pthread_cond_wait(&exit_signal, 
                              &exit_mutex);
        OpenExitDoor();                       // open exit door
        pthread_cond_signal(&exit_signal);    // signal to car that garage door is open

        while(carWaiting)                     // wait untill car has exited
            pthread_cond_wait(&exit_signal, 
                              &exit_mutex);
        CloseExitDoor();                      // close exit door
        pthread_cond_signal(&exit_signal);    // signal to car that exit door is closed
        pthread_mutex_unlock(&exit_mutex);    // unlock mutex
    }
    
    pthread_exit(NULL);
}

int main()
{
    pthread_mutex_init(&entry_mutex, NULL);
    pthread_mutex_init(&exit_mutex, NULL);
    pthread_cond_init(&entry_signal, NULL);
    pthread_cond_init(&exit_signal, NULL);
    
    pthread_create(&car, nullptr, car_function, nullptr);
    pthread_create(&entryGuard, nullptr, EntryGuard_function, nullptr);
    pthread_create(&exitGuard, nullptr, ExitGuard_function, nullptr);

    pthread_join(car, NULL);
    pthread_join(entryGuard, NULL);
    pthread_join(exitGuard, NULL);

    return 0;
}
