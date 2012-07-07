#ifndef H_GENERALEXCEPTION
#define H_GENERALEXCEPTION

#include <string>
#include <iostream>
#include "Log.h"

class GeneralException
{
public:
 GeneralException(std::string s) : m_s(s){};
    ~GeneralException(){};
    
    void logExceptionToFile(Log& logger);
    const char* message(){return m_s.c_str();}
protected:
    const std::string m_s;
};

#endif
