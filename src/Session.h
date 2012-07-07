#ifndef H_SESSION
#define H_SESSION

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpProcessor.h"
#include "Socket.h"
#include "ServerSocket.h"
#include "SocketException.h"
//#include "ConfigValues.h"
#include "Log.h"

#include <string>
#include <map>
#include <pthread.h>

class Session{
  ServerSocket *socket;
  Log *trafficLogger;
  Log *errorLogger;
 public:
  Session(ServerSocket*, Log*, Log*);
  ~Session(){ delete(socket); }
  void run();
};

#endif
