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

class Log
{
 public:
  Log(char* logfile, pthread_mutex_t* mutex);
  ~Log();
  
  void logException(char* exceptionThrown);
  void writeLog(char* strToWrite);
  const std::string getDateTime();
  
  template<class T> Log& operator<<(T const & out)
    {
      pthread_mutex_lock(loglock);
      m_stream << out; 
      pthread_mutex_unlock(loglock);
      return *this;
    }
  Log& operator<<(std::ostream&(*func)(std::ostream&))
    { 
      pthread_mutex_lock(loglock);
      func(m_stream);
      pthread_mutex_unlock(loglock);
      return *this;
    }
  void flush();
  void thread_lock(){pthread_mutex_lock(loglock);}
  void thread_unlock(){pthread_mutex_unlock(loglock);}
 private:
  std::ofstream m_stream;
  std::string output;
  pthread_mutex_t *loglock;
};
#endif
