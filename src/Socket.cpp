/**
 *  Socket.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "Socket.h"
#include <errno.h>

/**
 * This is just for when I compile it on my mac.
 * MSG_NOSIGNAL is a linux flag.
 */

#ifdef __APPLE__
#define NOSIGNAL SO_NOSIGPIPE
#else
#define NOSIGNAL MSG_NOSIGNAL
#endif

/**
 * Implementation of the Socket class.
 * It basically covers pretty standard functionality including
 * recv(), bind(), etc... but it wraps the standard function calls
 * in a method with special conditionals and then calls the original
 * functions that are living within the global namespace.
 */

Socket::Socket() : m_sock(-1)
{
    memset(&m_addr, 0, sizeof(m_addr));
}

Socket::~Socket()
{
    if (is_valid())
        ::close(m_sock);
}

bool Socket::create()
{
    m_sock = socket(AF_INET,
                    SOCK_STREAM,
                    0);
    if (! is_valid() )
        return false;
    
    int on = 1;
    if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*) &on, sizeof(on)) == -1 )
        return false;
    
    return true;
}

bool Socket::bind(const u_short port)
{
    if ( !is_valid() )
    {
        return false;
    }
    
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);

    //printf("%d\n",ntohs(m_addr.sin_port));
    std::cout << "Opened Server on port " << ntohs(m_addr.sin_port) << std::endl;

    int bind_return = ::bind (m_sock, (struct sockaddr *) &m_addr, sizeof(m_addr) );
    
    if (bind_return == -1)
    {
        return false;
    }
    
    return true;
}

bool Socket::listen() const
{
    if (!is_valid())
    {
        return false;
    }
    
    int listen_return = ::listen(m_sock, MAXCONNECTIONS);
    
    if (listen_return == -1)
    {
        return false;
    }
    
    return true;
}

bool Socket::accept(Socket* new_socket) const
{
    int addr_length = sizeof(new_socket->m_addr);
    new_socket->m_sock = 
        ::accept(m_sock, (sockaddr *)&new_socket->m_addr, (socklen_t *) &addr_length);
    if (new_socket->m_sock <= 0)
        return false;
    struct timeval timeout;
    timeout.tv_sec = 15;
    timeout.tv_usec = 0;
    if(setsockopt(new_socket->m_sock,SOL_SOCKET,SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)))
        return false;
    return true;
}

bool Socket::close(Socket* activeSocket) const
{
  
    if(::close(activeSocket->m_sock) != 0)
    {
        return false;
    }
    return true;
}

bool Socket::self_close() const
{
    if(::close(this->m_sock) != 0)
    {
        //printf("%s\n",strerror(errno));
        std::cout << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

bool Socket::send(const std::string s) const
{
    int status = ::send (m_sock, s.c_str(), s.size(), NOSIGNAL);
    if (status == -1)
        return false;
    else
        return true;
}

bool Socket::send(const char* data, const int size) const
{
    int status = ::send(m_sock, data, size, NOSIGNAL);
    if(status == -1)
        return false;
    else
        return true;
}

int Socket::recv (std::string& s) const
{
    char buf[MAXRECV + 1];
    
    memset(buf, 0, MAXRECV + 1);
    
    int status = ::recv(m_sock, buf, MAXRECV, 0);
    
    if (status == -1)
    {
        return -1;
    }
    else if (status == 0)
    {
        return 0;
    }
    else
    {
        s = buf;
        return status;
    }
}

bool Socket::connect (const std::string host, const int port)
{
    if (!is_valid()) return false;
    
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    
    int status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);
    
    if (errno == EAFNOSUPPORT) return false;
    
    status = ::connect(m_sock, (sockaddr *) &m_addr, sizeof(m_addr));
    
    if (status == 0)
        return true;
    else
        return false;
}

void Socket::set_non_blocking(const bool b)
{
    int opts;
    
    opts = fcntl(m_sock,
                 F_GETFL);
    
    if (opts < 0)
        return;
    if(b)
        opts = (opts | O_NONBLOCK);
    else
        opts = (opts & ~O_NONBLOCK);
    
    fcntl(m_sock,
          F_SETFL,
          opts);
}
