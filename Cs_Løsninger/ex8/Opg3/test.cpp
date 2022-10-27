#include <iostream>
#include <SmartPointer.hpp>

int main(int argc , char* argv [])
{
    //***** Test with string *****
    SmartPointer<std::string> A(new std::string("A"));
    std::cout << "SmartPointer A pointing to string '" << *A.get() << "' used " << A.getCount() << " times\n\n";

    SmartPointer<std::string> B(new std::string("B"));
    std::cout << "SmartPointer A pointing to string '" << *A.get() << "' used " << A.getCount() << " times\n";
    std::cout << "SmartPointer B pointing to string '" << *B.get() << "' used " << B.getCount() << " times\n\n";

    std::cout << "***** Assigning smartpointer B to A *****\n\n"; 
    A = B;
    std::cout << "SmartPointer A pointing to string '" << *A.get() << "' used " << A.getCount() << " times\n";
    std::cout << "SmartPointer B pointing to string '" << *B.get() << "' used " << B.getCount() << " times\n\n";

    std::cout << "***** Creating new smartpointer C pointing to same as A *****\n\n";
    SmartPointer<std::string> C = A;
    std::cout << "SmartPointer A pointing to string '" << *A.get() << "' used " << A.getCount() << " times\n";
    std::cout << "SmartPointer B pointing to string '" << *B.get() << "' used " << B.getCount() << " times\n";
    std::cout << "SmartPointer C pointing to string '" << *C.get() << "' used " << C.getCount() << " times\n\n";
    

    /***** Test with int *****
    SmartPointer<int> A(new int(12));
    std::cout << "SmartPointer A pointing to int '" << *A.get() << "' used " << A.getCount() << " times\n\n";

    SmartPointer<int> B(new int(45));
    std::cout << "SmartPointer A pointing to int '" << *A.get() << "' used " << A.getCount() << " times\n";
    std::cout << "SmartPointer B pointing to int '" << *B.get() << "' used " << B.getCount() << " times\n\n";

    std::cout << "***** Assigning smartpointer B to A *****\n\n"; 
    A = B;
    std::cout << "SmartPointer A pointing to int '" << *A.get() << "' used " << A.getCount() << " times\n";
    std::cout << "SmartPointer B pointing to int '" << *B.get() << "' used " << B.getCount() << " times\n\n";

    std::cout << "***** Creating new smartpointer C pointing to same as A *****\n\n";
    SmartPointer<int> C = A;
    std::cout << "SmartPointer A pointing to int '" << *A.get() << "' used " << A.getCount() << " times\n";
    std::cout << "SmartPointer B pointing to int '" << *B.get() << "' used " << B.getCount() << " times\n";
    std::cout << "SmartPointer C pointing to int '" << *C.get() << "' used " << C.getCount() << " times\n\n";
    */

    return 0;
};


