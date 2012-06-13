//
//  Socket.h
//  
//
//  Created by Derek Parker and Kyle Nusbaum on 6/5/12.
//  Copyright (c) 2012 Splache. All rights reserved.
//

#ifndef _Socket_class
#define _Socket_class

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>

#define MAXHOSTNAME 200
#define MAXCONNECTIONS 5
#define MAXRECV 500

using namespace std;

class Socket
{
private:
    int m_sock;
    sockaddr_in m_addr; // sockaddr_in is defined in netinet/in.h
public:
    Socket();
    virtual ~Socket();
    
    /* Server initialization */
    bool create();
    bool bind(const int port);
    bool listen() const;
    bool accept (Socket&) const;
    
    /* Client initialization */
    bool connect (const string host, const int port);
    
    /* Data Transmission */
    bool send(const string) const;
    int recv(string&) const;
    
    void set_non_blocking(const bool);
    bool is_valid() const { return m_sock != -1; }
};

#endif
