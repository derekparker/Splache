/**
 *  SocketException.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include <iostream>
#include "SocketException.h"

SocketException::logExceptionToFile(Log& logger)
{
    logger.logException(m_s);
}