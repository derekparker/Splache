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
  //socket:        The socket we'll be communicating through
  //trafficLogger: The logger we'll use to log traffic on
  //errorLogger:   The logger we'll use to log errors on
  ServerSocket *socket;
  Log *trafficLogger;
  Log *errorLogger;
  
 public:
  Session(ServerSocket*, Log*, Log*);
  ~Session(){ delete(socket); }

  //Start receiving requests
  void run();
};

#endif
