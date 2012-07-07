/**  
 *  Log.cpp
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "Log.h"

using namespace std;

Log::Log(char* logfile, pthread_mutex_t *mutex)
{
  loglock = mutex;
  m_stream.open(logfile, ios::app);
    if(!m_stream.is_open())
      {
	printf("Could not open logfile: %s\n",logfile);
      }
    else printf("%s opened for log.\n",logfile);
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

