#include <osapi/Mutex.hpp>
#include <osapi/linux/Mutex.hpp>

namespace osapi
{
  Mutex::Mutex()
  {
    if(pthread_mutex_init(&mut_, NULL) != 0) throw MutexError();;
  }

  void Mutex::lock()
  {
    if(pthread_mutex_lock(&mut_)!=0) throw MutexError();
  }
  
  void Mutex::unlock()
  {
    if(pthread_mutex_unlock(&mut_)!=0) throw MutexError();
  }

  Mutex::~Mutex()
  {
    // Needed for incomplete type - MUST be in the cpp file where the pimpl is known!!!
	  pthread_mutex_destroy(&mut_);
  }
  
}