/**
 *  Splache.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 *  Cause we're awesome.
 */

#include "Splache.h"

#define INITIAL_THREADS 50

int main(int argc, char* argv[]) 
{  
  std::cout << "Initializing server..." << std::endl;

  // parse the config file
  ConfigParser *parser = new ConfigParser;
  parser->parseConfigFile(config::configValues);
  delete(parser);  // destroy for io cleanup

  if(config::configValues["GOOD_CONFIG"] == "false")
      return 1;
  
  const char* PATH_TO_TRAFFICLOG = (char*)"log/splache.traffic";
  const char* PATH_TO_LOGFILE    = config::configValues["PATH_TO_LOGFILE"].c_str();
  const int   PORT               = atoi( config::configValues["PORT"].c_str() );
  
  pthread_mutex_t errorLoglock;
  pthread_mutex_t trafficLoglock;
  if(pthread_mutex_init(&errorLoglock,NULL) != 0)
      std::cout << "Error creating mutex." << std::endl;
  if(pthread_mutex_init(&trafficLoglock,NULL) != 0)
      std::cout << "Error creating mutex." << std::endl;
  
  // create the loggers.
  Log errorLogger(PATH_TO_LOGFILE, &errorLoglock, config::configValues["ERROR_VERBOSE"] == "true");
  Log trafficLogger(PATH_TO_TRAFFICLOG, &trafficLoglock, config::configValues["TRAFFIC_VERBOSE"] == "true");
  
  auto workers = std::list<Worker*>();
  
  try 
    {
      // start listening on port carried from config file.
      ServerSocket server( PORT );     
      
      // start thread pool
      pthread_t newThread;
      errorLogger<<"Creating "<<INITIAL_THREADS<<" threads..."<<std::endl;
      for(int i = 0; i < INITIAL_THREADS; i++)
	{
	  Worker *w = new Worker(&server,&trafficLogger, &errorLogger);
	  workers.push_back(w);
	  int error = pthread_create(&newThread,NULL,run::spawn_thread,(void*)w);
	  if(error != 0)
              std::cout << "Thread Error" << std::endl;
	}

      pthread_join(newThread,NULL);
    }
  
  catch (SocketException *e) 
    {
        //std::cout << "fail" << std::endl;
      e->logExceptionToFile(errorLogger);
      delete(e);
    }
  
  return 0;
}
