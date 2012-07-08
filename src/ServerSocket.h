/**
 *  ServerSocket.h
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#ifndef _ServerSocket_class
#define _ServerSocket_class

#include "Socket.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "SocketException.h"

using namespace std;

class ServerSocket : private Socket
{
  //Log *logger;

 public:
  //Open and listen on the port
  ServerSocket (int port);

  ServerSocket (){};
  virtual ~ServerSocket();

  //overloading the stream operators
  const ServerSocket& operator << (const string&) const;
  const ServerSocket& operator >> (string&) const;
  ServerSocket& operator << (HttpResponse*);
  ServerSocket& operator >> (HttpRequest*);
  
  //Accept an incoming connection into a new socket.
  void accept (ServerSocket*);

  //Close a socket
  void close (ServerSocket*);
  
  //Close self
  void self_close ();

  //get the remote address
  sockaddr_in remoteAddr(){return Socket::remoteAddr();}

  //void setLogger(Log* logger){this->logger = logger;}
};

#endif
