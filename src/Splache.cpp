/**
 *  Splache.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "Splache.h"

/*TEMPORARY*/
//#include <sys/socket.h>
//#include <netinet/in.h>
#define MAXTHREADS 10


static void daemonize();
static void spawn_thread(Session* session);
static pthread_t getThread();

queue<pthread_t> threadQueue;
int threadCount;

int main(int argc, char* argv[]) 
{
  //daemonize();

  threadQueue = queue<pthread_t>();
  // PATH_TO_LOGFILE will be replaced with a configparser class member <map>
  char* PATH_TO_TRAFFICLOG = (char*)"../logs/splache.traffic";
  char* PATH_TO_LOGFILE = (char*)"../logs/splache.log";
  Log errorLogger(PATH_TO_LOGFILE);
  Log trafficLogger(PATH_TO_TRAFFICLOG);

  try 
    {
      ServerSocket server(30000);     
      
      while (true) 
        {
	  ServerSocket *sock = new ServerSocket();
	  server.accept(sock);
	  Session *s = new Session(sock, &trafficLogger, &errorLogger);
	  spawn_thread(s);

        }
    }
  
  catch (SocketException *e) 
    {
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
  
  //Change working directory. (Eventually pull this from config?)
  if(chdir("/") < 0)
    exit(1);

  //Redirect standard IO streams to null.
  freopen("/dev/null/", "r", stdin);
  freopen("/dev/null/", "w", stdout);
  freopen("/dev/null/", "w", stderr);
  
}

static void spawn_thread(Session* session)
{
  session->run();
  delete(session);
}

static pthread_t getThread()
{
  
}
