#include <iostream>
#include <SmartString.hpp>

int main(int argc , char* argv [])
{
    SmartString A(new std::string("A")); //Constructor call
    std::cout << "String length: " << A ->length () << std::endl;

    SmartString B(new std::string("B")); //Constructor call

    SmartString C(new std::string("C")); //Constructor call
    C = B;                              //Assignment operator call

    SmartString D(new std::string("D")); //Constructor call

    SmartString E = D;                  //Copy Constructor call

    return 0;
};
