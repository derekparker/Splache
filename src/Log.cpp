/**  
 *  Log.cpp
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include <iostream>
#include "Log.h"

Log::Log(char* logfile)
{
    m_stream.open(logfile);
}

Log::logException(char* exceptionThrown)
{
    m_stream << getDateTime() << ": " << exceptionThrown << endl;
}

Log::getDateTime()
{
    time_t now = time(0);
    struct tm t;
    char buf[80];
    t = *localtime(&now);
    
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &t);
    
    return buf;
}

Log::~Log()
{
    m_stream.close();
}