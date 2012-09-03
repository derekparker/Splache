#include "run.h"

namespace run
{
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
      //printf("Spawning Thread\n");
    Worker *worker = (Worker*)arg;
    worker->run();
    delete(worker);
    std::cout << "Thread dying." << std::endl;
  }
}
