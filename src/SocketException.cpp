/**
 *  SocketException.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include <iostream>
#include "SocketException.h"

void SocketException::logExceptionToFile(Log& logger)
{
  logger.logException((char*)m_s.c_str());
}
