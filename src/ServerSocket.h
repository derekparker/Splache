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
  Log *logger;
public:
    ServerSocket (int port);
    ServerSocket (){};
    virtual ~ServerSocket();
    
    const ServerSocket& operator << (const string&) const;
    const ServerSocket& operator >> (string&) const;
    ServerSocket& operator << (HttpResponse*);
    ServerSocket& operator >> (HttpRequest*);

    void accept (ServerSocket*);
    void close (ServerSocket*);
    void self_close ();
    sockaddr_in remoteAddr(){return Socket::remoteAddr();}
    void setLogger(Log* logger){this->logger = logger;}
};

#endif
