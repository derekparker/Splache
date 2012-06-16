//
//  Log.h
//  
//
//  Created by Derek Parker and Kyle Nusbaum on 6/15/12.
//  Copyright (c) 2012 Splache. All rights reserved.
//

#ifndef _Log_h
#define _Log_h

#include <fstream>
#include <string>
#include <time.h>

class Log
{
public:
    Log(char* logfile);
    ~Log();
    
    void logException(char* exceptionThrown);
    
    const std::string getDateTime();
    
private:
    fstream m_stream;
    std::string output;
}

#endif
