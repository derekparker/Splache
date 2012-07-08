/**
 *  Socket.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "ServerSocket.h"

using namespace std;

ServerSocket::ServerSocket (int port)
{
    if ( ! Socket::create() ) 
    {
        throw new SocketException ("Could not create server socket.");
    }
    
    if ( ! Socket::bind (port) )
    {
        throw new SocketException ( "Could not bind to port.");
    }
    
    if (! Socket::listen() )
    {
        throw new SocketException ( "Could not listen to port.");
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
        throw new SocketException("Could not write to socket.");
    }
    
    return *this;
}

const ServerSocket& ServerSocket::operator >> (string& s) const
{
  
  Socket::recv(s);
  /*
   * I actually want to keep this due to the fact
   * that in the config file the persistant 
   * connection will be optional. I want it to
   * be optional because sometimes persistant 
   * connections can be bad and lead to massive 
   * security vulnerabilities (DDOS attacks)
   */
  /*
    We'll put this back once the config is done.
    If you want to keep this, we need to check the errno
    to see if the socket has an error or if it has timed out.
    We don't want to log timeouts I don't think.
  */
  /*
    if (! Socket::recv(s))
    {
      throw new SocketException("Could not read from socket.");
    }
  */
  return *this;
}

ServerSocket& ServerSocket::operator << (HttpResponse* response)
{
  if( response == NULL )
    {
      throw new SocketException("Cannot send null response.");
    }
  response->makeResponseBuffer();
  if (! Socket::send(response->Response(), response->ContentLength()) )
    {
      throw new SocketException("Could not write to socket.");
    }
  return *this;
  
}

ServerSocket& ServerSocket::operator >> (HttpRequest* request)
{
  string s;
  *this >> s;
  if(s == "")
    return *this;
  request->setRequest((char*)s.c_str());
  return *this;
}


void ServerSocket::accept(ServerSocket* sock)
{
    if (! Socket::accept(sock) )
    {
        throw new SocketException("Could not accept socket.");
    }
}

void ServerSocket::close(ServerSocket* sock)
{
  if(! Socket::close(sock) )
    {
      throw new SocketException("Could not close socket.");
    }
}

void ServerSocket::self_close()
{
  if(! Socket::self_close() )
    {
      throw new SocketException("Could not close socket.");
    }
}
