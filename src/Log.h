/**  
 *  Log.h
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#ifndef _Log_h
#define _Log_h

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

class Log
{
 public:
    Log(char* logfile);
    ~Log();

    void logException(char* exceptionThrown);
    void writeLog(char* strToWrite);
    const std::string getDateTime();
    
    template<class T> Log& operator<<(T const & out){ m_stream << out; return *this; }
    Log& operator<<(std::ostream&(*func)(std::ostream&)){ func(m_stream); return *this; }
    void flush();
private:
    std::ofstream m_stream;
    std::string output;
};
#endif
