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
#include <pthread.h>
#include "ConfigValues.h"


class Log
{
 public:
    Log(const char* logfile, pthread_mutex_t* mutex, bool isVerbose);
  ~Log();
  
  //log an exception
  void logException(char* exceptionThrown);

  //writes to log
  void writeLog(char* strToWrite);

  //get the date
  const std::string getDateTime();

  //Stream operator overrides. Locks the mutex to make sure we don't 
  //end up with gibberish
  template<class T> Log& operator<<(T const & out)
    {
      pthread_mutex_lock(loglock);
      m_stream << out;
      if(config::configValues["ERROR_VERBOSE"] == "true")
          std::cout<<out;
      pthread_mutex_unlock(loglock);
      return *this;
    }
  Log& operator<<(std::ostream&(*func)(std::ostream&))
    { 
      pthread_mutex_lock(loglock);
      func(m_stream);
      if(config::configValues["ERROR_VERBOSE"] == "true")
          func(std::cout);
      pthread_mutex_unlock(loglock);
      return *this;
    }

  //Flush the stream
  void flush();
  
  //A method used to lock the log's mutex
  void thread_lock(){pthread_mutex_lock(loglock);}

  //A method used to unlock the log's mutex
  void thread_unlock(){pthread_mutex_unlock(loglock);}
 
 private:
  //m_stream:    The filestream 
  //loglock:     The mutex for locking the filestream
  std::ofstream m_stream;
  //std::string output;
  pthread_mutex_t *loglock;
  bool verbose;
};
#endif
