#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;

/* create mutex */
pthread_mutex_t mtx;

/* allocate dynamic memory and initialize dynamic mutex */
void *mem = malloc(pthread_mutex_init(&mtx, NULL)); 

void* hello_func(void* arg)
{
    int* str = (int*) arg;
    
    /* start of critical section */

    pthread_mutex_lock(&mtx); 
    for (int i = 0; i < 10; i++)
    {
        cout << "Hello #" << i << " from thread: " << *str << endl;
        sleep(1);
    }
    pthread_mutex_unlock(&mtx);

    /* end of critical section */

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

/* destroy dynamically initialized mutex */
pthread_mutex_destroy(&mtx);

/* free dynamically allocated memory */
free(mem);

/* remove dangling pointer */
mem = NULL;

return 0;
}
