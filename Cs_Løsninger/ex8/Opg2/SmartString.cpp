#include <SmartString.hpp>
#include <iostream>

SmartString::SmartString(std::string* str) : str_(str), counter_(new unsigned int(1))
{
    std::cout << "constructor " << *str << " called\n";
}
SmartString::~SmartString()
{
    std::cout << "destructor " << *str_ << " called. Smart pointer counter: " << *counter_ << "\n";
    --(*counter_);

    if(*counter_ == 0)
    {
        delete str_;
        delete counter_;
    }
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

SmartString::SmartString(const SmartString& other) : str_(other.str_), counter_(other.counter_)
{
    ++(*counter_);
    std::cout << "Copy-constructor for " << *other.str_ << " called\n";
}

void SmartString::swap(SmartString& other)
{
    std::swap(str_, other.str_);
    std::swap(counter_, other.counter_);
}

SmartString& SmartString::operator=(const SmartString& other)
{
    SmartString(other).swap(*this);
    std::cout << "assignment-operator for " << *other.str_ << " called\n";
    return *this;
}