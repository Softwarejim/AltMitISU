#include <pthread.h>
#include <iostream>
using namespace std;

void *hello_func(void *arg)
{
    string *str = static_cast<string*>(arg);
    printf("%s", str->data());
    return nullptr;
}

int main(int argc, char *argv[])
{
    pthread_t th;

    string str = "Hello World\n";

    pthread_create(&th, NULL, hello_func, &str);     

    pthread_join(th, nullptr);

    return 0;
}
