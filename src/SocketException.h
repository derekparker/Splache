/**
 *  SocketException.h
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#ifndef _SocketException_class
#define _SocketException_class

#include <string>
#include <iostream>
#include "Log.h"

class SocketException
{
public:
    SocketException(std::string s) : m_s(s){};
    ~SocketException(){};
    
    void logExceptionToFile(Log& logger);
    const char* message(){return m_s.c_str();}
private:
    const std::string m_s;
};


#endif
