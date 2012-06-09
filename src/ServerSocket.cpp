//
//  Socket.cpp
//  
//
//  Created by Derek Parker and Kyle Nusbaum on 6/5/12.
//  Copyright (c) 2012 Splache All rights reserved.
//

#include "ServerSocket.h"
#include "SocketException.h"

using namespace std;

ServerSocket::ServerSocket (int port)
{
    if ( ! Socket::create() ) 
    {
        throw SocketException ("Could not create server socket.");
    }
    
    if ( ! Socket::bind (port) )
    {
        throw SocketException ( "Could not bind to port.");
    }
    
    if (! Socket::listen() )
    {
        throw SocketException ( "Could not listen to port.");
    }
}

ServerSocket::~ServerSocket(){}


/**
 * Here I am overloading the << and >> operators because
 * I have an interesting idea for the transferring of
 * data that you will see later when I implement the
 * main function.
 */
const ServerSocket& ServerSocket::operator << (const string& s) const
{
    if (! Socket::send(s) )
    {
        throw SocketException("Could not write to socket.");
    }
    
    return *this;
}

const ServerSocket& ServerSocket::operator >> (string& s) const
{
    if (! Socket::recv(s) )
    {
        throw SocketException("Could not read from socket.");
    }
    
    return *this;
}

void ServerSocket::accept(ServerSocket& sock)
{
    if (! ServerSocket::accept(sock) )
    {
        throw SocketException("Could not accept socket.");
    }
}