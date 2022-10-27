#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;

unsigned int shared = 0;
void* inc(void* d)
{
        for (int i = 0; i < 10; i++)
    {
        shared++;
        sleep(1);
    }
    
    pthread_exit(NULL);
}
void* read(void* d)
{
     for (int i = 0; i < 10; i++)
    {
        cout << "Shared is: " << shared << endl;
        sleep(1);
    }
    
    pthread_exit(NULL);
}


int main()
{
pthread_t incrementer, reader;

pthread_create(&incrementer, nullptr, inc,static_cast <void*>(&shared));
pthread_create(&reader, nullptr, read,static_cast <void*>(&shared));

pthread_join(incrementer, nullptr);
pthread_join(reader, nullptr);

return 0;
}
