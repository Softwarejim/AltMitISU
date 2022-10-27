#include <string>

class SmartString
{
private:
    std::string* str_;
    unsigned int* counter_;

public:
    SmartString(std::string* str);
    SmartString(const SmartString& other);
    ~SmartString();
    std::string* get();
    void swap(SmartString& other);
    std::string* operator->();
    std::string& operator*();
    SmartString& operator=(const SmartString& other);
};