#include "Vector.hpp"
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

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
    sleep(1);
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    int NTHREADS = atoi(argv[1]);
    Vector vector;

    if (0 < NTHREADS && NTHREADS <= 100)
    {
      cout << "Creating " << NTHREADS << " thread(s)" << endl;
      pthread_t threads[NTHREADS];

      for (int i = 0; i < NTHREADS; i++)
      {
        pthread_create(&threads[i], nullptr, writer,
                       static_cast<void *>(&vector));
      }

      cout << "Running test" << endl;

      for (int i = 0; i < NTHREADS; i++)
      {
        pthread_join(threads[i], nullptr);
      }

      cout << "Test completed with " << count_err << " errors"<< endl;
    }

    else
      cout << "No. of threads cannot be less than 1 or more than 100" << endl;
  }

  else
  {
    cout << "Not enough arguments to program." << endl;
    cout << "Please specify no. of threads to be created (between 1 and 100)" << endl;
  }

  return 0;
}
