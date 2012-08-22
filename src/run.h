#ifndef RUN_H
#define RUN_H
#include <stdio.h>
#include <pthread.h>
#include "Worker.h"
#include <sys/stat.h>

namespace run
{
  static void daemonize();

  void *spawn_thread(void*);
}

#endif
