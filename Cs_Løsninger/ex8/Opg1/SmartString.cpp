#include <SmartString.hpp>
#include <iostream>

SmartString::SmartString(std::string* str) : str_(str)
{}

SmartString::~SmartString()
{
    delete str_;
    std::cout << "Destructor called. smart pointer destroyed.\nString pointer contains:" << *str_;
}

std::string* SmartString::get()
{
    return str_;
}

std::string* SmartString::operator->()
{
    return str_;
}

std::string& SmartString::operator*()
{
    return *str_;
}