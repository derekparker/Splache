//
//  SocketException.cpp
//  
//
//  Created by Derek Parker on 6/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SocketException.h"

SocketException::logExceptionToFile()
{
    Log logger;
    logger.logException(m_s)
    delete logger;
}