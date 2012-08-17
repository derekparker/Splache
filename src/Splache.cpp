/**
 *  Splache.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 *  Cause we're awesome.
 */

#include "Splache.h"

#define INITIAL_THREADS 50

static void daemonize();
void *spawn_thread(void*);

int main(int argc, char* argv[]) 
{  
  std::cout << "Initializing server" << std::endl;
  std::cout << "..." << std::endl;

  // Parse the config file
  ConfigParser *parser = new ConfigParser;
  parser->parseConfigFile(config::configValues);
  delete(parser);  // Destroy for io cleanup
  

  const char* PATH_TO_TRAFFICLOG = (char*)"../logs/splache.traffic";
  const char* PATH_TO_LOGFILE    = config::configValues["PATH_TO_LOGFILE"].c_str();
  const int   PORT               = atoi( config::configValues["PORT"].c_str() );

  std::cout << PORT << std::endl;
  
  pthread_mutex_t errorLoglock;
  pthread_mutex_t trafficLoglock;
  if(pthread_mutex_init(&errorLoglock,NULL) != 0)
    printf("Error creating mutex.");
  if(pthread_mutex_init(&trafficLoglock,NULL) != 0)
    printf("Error creating mutex.");
  
  //Create the loggers.
  Log errorLogger(PATH_TO_LOGFILE, &errorLoglock);
  Log trafficLogger(PATH_TO_TRAFFICLOG, &trafficLoglock);
  
  auto workers = std::list<Worker*>();
  
  try 
    {
      std::cout << "win" << std::endl;
      //Start listening on port carried from config file.
      ServerSocket server( PORT );     
      
      /*
	Instead of spawning and letting die threads for each connection, we'll use a worker thread pool, 
	as that seems to be the standard, and a more stable design from what I've read.
      */
      pthread_t newThread;
      for(int i = 0; i < INITIAL_THREADS; i++)
	{
	  Worker *w = new Worker(&server,&trafficLogger, &errorLogger);
	  workers.push_back(w);
	  int error = pthread_create(&newThread,NULL,spawn_thread,(void*)w);
	  if(error != 0)
	    printf("Thread Error");
	}

      pthread_join(newThread,NULL);
    }
  
  catch (SocketException *e) 
    {
      std::cout << "fail" << std::endl;
      e->logExceptionToFile(errorLogger);
      delete(e);
    }
  
  return 0;
}

static void daemonize()
{
  pid_t pid;
  pid = fork();
  if(pid < 0)
    exit(-1);
  
  //If original process, exit.
  if(pid > 0)
    exit(0);
  
  //If we are executing this, we are the child process.
  //Change the file usermask.
  umask(0);
  
  //Create new group and make child the leader
  if(setsid() < 0)
    exit(1);
  
  //Change working directory.
  if(chdir(config::configValues["WORKING_DIRECTORY"].c_str()) < 0)
    exit(1);
  
  //Redirect standard IO streams to null.
  freopen("/dev/null/", "r", stdin);
  freopen("/dev/null/", "w", stdout);
  freopen("/dev/null/", "w", stderr);
}

void *spawn_thread(void *arg)
{
  printf("Spawning Thread\n");
  Worker *worker = (Worker*)arg;
  worker->run();
  delete(worker);
  printf("Thread dying.\n");
}
