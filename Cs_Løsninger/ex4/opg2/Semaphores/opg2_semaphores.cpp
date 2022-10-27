#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include "Vector.hpp"
using namespace std;
sem_t sem;


int us = 1;
int count_err = 0;

void* writer(void* arg)
{
    int ret;
    Vector *vec = (Vector *)arg;
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&sem);
        ret = vec->setAndTest(pthread_self());
        sem_post(&sem);
        if(!ret)
        {
            cout << "Errer detected" << endl;
            count_err++;
        }
        usleep(us);
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    if(argc >1)
    {
        int antalTH = atoi(argv[1]);
        us = atoi(argv[3]) * 1000;
        Vector vector(atoi(argv[2]));
        sem_init(&sem,0,1);
        if(0 < antalTH && antalTH <= 100)
        {
            cout << "Creating " << antalTH << " thread(s)" << endl;
            cout << "Creating vector with size " << vector.getSize() << endl;
            cout << "Setting delay to " << us / 1000 << " ms" << endl;
            
            pthread_t threads[antalTH];

            for (int i = 0; i < antalTH; i++)
            {
                pthread_create(&threads[i], nullptr, writer, static_cast<void *>(&vector));
            }
            cout << "\nRunning test:" << endl;

            for(int i = 0; i < antalTH; i++)
            {
                pthread_join(threads[i], NULL);
            }       
            cout << "Test completed with " << count_err << " errors"<< endl;
        }
        else 
            cout << "No. of threads cannot be less than 1 og more than 100" << endl;
    }
    else
    {
        cout << "Not enough arguments to program." << endl;
        cout << "Please specify no. of threads to be created (between 1 and 100)" << endl;
    }
    return 0;
}
