#include <string>

class SmartString
{
private:
    SmartString(const SmartString& other);
    SmartString& operator=(const SmartString& other);
    
    std::string* str_;

public:
    SmartString(std::string* str);
    ~SmartString();
    std::string* get();
    std::string* operator->();
    std::string& operator*();
};