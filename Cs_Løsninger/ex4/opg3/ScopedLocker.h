#include <pthread.h>
#include <unistd.h>

class ScopedLocker
{
public:

    ScopedLocker(pthread_mutex_t& mtx) : mtx_local(&mtx)
    {
        pthread_mutex_lock(mtx_local);
    }

    ~ScopedLocker()
    {
        pthread_mutex_unlock(mtx_local);
    }

private:
    pthread_mutex_t* mtx_local;
   
};