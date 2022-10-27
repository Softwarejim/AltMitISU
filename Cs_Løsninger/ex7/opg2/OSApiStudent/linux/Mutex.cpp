#include <osapi/Mutex.hpp>

namespace osapi
{
    Mutex::Mutex()
    {
       if (pthread_mutex_init(&mut_, NULL)) throw MutexError();
    }

    void Mutex::lock()
    {
        if (pthread_mutex_lock(&mut_)) throw MutexError();
    }

    void Mutex::unlock()
    {
        if (pthread_mutex_unlock(&mut_)) throw MutexError();
    }

    Mutex::~Mutex()
    {
        pthread_mutex_destroy(&mut_);
    }

}