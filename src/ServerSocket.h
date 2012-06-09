//
//  ServerSocket.h
//  
//
//  Created by Derek Parker and Kyle Nusbaum on 6/5/12.
//  Copyright (c) 2012 Splache. All rights reserved.
//

#ifndef _ServerSocket_class
#define _ServerSocket_class

#include "Socket.h"

using namespace std;

class ServerSocket : private Socket
{
public:
    ServerSocket (int port);
    ServerSocket (){};
    virtual ~ServerSocket();
    
    const ServerSocket& operator << (const string&) const;
    const ServerSocket& operator >> (string&) const;
    
    void accept (ServerSocket&);
}

#endif
