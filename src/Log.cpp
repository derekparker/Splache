/**  
 *  Log.cpp
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "Log.h"

using namespace std;

Log::Log(const char* logfile, pthread_mutex_t *mutex, bool isVerbose)
{
    verbose = isVerbose;
    loglock = mutex;
    m_stream.open(logfile, ios::app);
    if(config::configValues["ERROR_VERBOSE"] == "true")
        if(!m_stream.is_open())
        {
            cout << "Could not open logfile: " << logfile << endl;
        }
        else cout << logfile << " opened for log." << endl;
}

void Log::logException(char* exceptionThrown)
{
    m_stream << "Exception Thrown: " << getDateTime() << ": " << exceptionThrown << endl;
}

void Log::writeLog(char* strToWrite)
{
    m_stream << strToWrite << endl;
}

const string Log::getDateTime()
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

void Log::flush()
{
    m_stream.flush();
}

