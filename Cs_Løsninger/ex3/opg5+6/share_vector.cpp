#include "Vector.hpp"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int us = 1;
int count_err = 0;

void *writer(void *d)
{
  int ret; 
  Vector *vec = (Vector *)d;
  
  for (int i = 0; i < 10; i++)
  {
    ret = vec->setAndTest(pthread_self());
    if (!ret) 
    {
        cout << "Error detected" << endl;
        count_err++;
    }
    usleep(us);
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    int NTHREADS = atoi(argv[1]);
    us = atoi(argv[3]) * 1000;
    Vector vector(atoi(argv[2]));

    if (0 < NTHREADS && NTHREADS <= 100)
    {
      cout << "Creating " << NTHREADS << " thread(s)" << endl;
      cout << "Creating vector with size " << vector.getSize() << endl;
      cout << "Setting delay to " << us / 1000 << " ms" << endl;

      pthread_t threads[NTHREADS];

      for (int i = 0; i < NTHREADS; i++)
      {
        pthread_create(&threads[i], nullptr, writer,
                       static_cast<void *>(&vector));
      }

      cout << "\nRunning test:" << endl;

      for (int i = 0; i < NTHREADS; i++)
      {
        pthread_join(threads[i], NULL);
      }

      cout << "Test completed with " << count_err << " errors"<< endl;
    }
    else
      cout << "No. of threads cannot be less than 1 or more than 100" <<endl;
  }
  else
  {
    cout << "Not enough arguments to program. \nPlease type the following:" << endl;
    cout << "./share_vector <no. of threads> <vector size> <delay in ms>" << endl;
  }

  return 0;
}
