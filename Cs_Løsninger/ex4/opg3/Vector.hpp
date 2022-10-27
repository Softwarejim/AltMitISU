#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#pragma once
#include <iostream>
#include "ScopedLocker.h"
using namespace std;
//=======================================================
// Class: Vector
// contains a size_-size vector of integers.
// Use the function setAndTest to set all elements
// of the vector to a certain value and then test that
// the value is indeed correctly set
//=======================================================
class Vector
{
public:
   Vector(unsigned int size = 10000) : size_(size)
      {        
         pthread_mutex_init(&mut_,nullptr);  //initiate mutex

         vector_ = new int[size_];
         set(0);
      }

   ~Vector()
      {
         delete[] vector_;

      }

   void setSize(unsigned int size)
      {
         delete[] vector_;
         size_ = size;
         vector_ = new int[size_];
         set(0);
      }

   int getSize() const
      {
         return size_;
      }

   bool setAndTest(int n)
      {
         ScopedLocker s(mut_); //locker
         set(n);

         return test(n); //unlocker - outscoped
      }

private:
   void set(int n)
      {
         for(unsigned int i=0; i<size_; i++) vector_[i] = n;
      }

   bool test(int n)
      {
         for(unsigned int i=0; i<size_; i++) if(vector_[i] != n) return false;
         return true;
      }

   int*           vector_;
   unsigned int   size_;
   pthread_mutex_t mut_; // mutex pointer
   
};

#endif
