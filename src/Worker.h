#ifndef H_WORKER
#define H_WORKER

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpProcessor.h"
#include "Socket.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include "ConfigParser.h"
#include "ConfigValues.h"
#include "Log.h"

#include <string>
#include <map>
#include <pthread.h>

class Worker{
  //server_socket: The listening socket
  //trafficLogger: The logger we'll use to log traffic on
  //errorLogger:   The logger we'll use to log errors on
  ServerSocket *server_socket;
  Log  *trafficLogger;
  Log  *errorLogger;
  bool shouldRun;

  //Handle a socket that's accepted a connection.
  bool processConnection(ServerSocket &socket);

 public:
  Worker(ServerSocket*, Log*, Log*);
  ~Worker(){}

  //Start receiving requests
  void run();
  void kill();

};

#endif
