//
//  SocketException.h
//  
//
//  Created by Derek Parker and Kyle Nusbaum on 6/5/12.
//  Copyright (c) 2012 Splache. All rights reserved.
//

#ifndef _SocketException_class
#define _SocketException_class

#include <string>

class SocketException
{
public:
    SocketException(std::string s) : m_s(s){};
    ~SocketException(){};
    
    std::string description(){return m_s;}

private:
    std::string m_s;
    
};


#endif
