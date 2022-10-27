#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;


void* hello_func(void* arg)
{
    int* str = (int*) arg;
    
    for (int i = 0; i < 10; i++)
    {
        cout << "Hello #" << i << " from thread: " << *str << endl;
        sleep(1);
    }
    
    return nullptr;
}

int main(int argc, char* argv[])
{

pthread_t th1, th2;
int a[2] = { 0, 1 };

pthread_create(&th1, nullptr, hello_func,static_cast <void*>(&a[0]));
pthread_create(&th2, nullptr, hello_func,static_cast <void*>(&a[1]));

pthread_join(th1, nullptr);
pthread_join(th2, nullptr);

return 0;
}
