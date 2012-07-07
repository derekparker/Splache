/**
 *  configValues.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#ifndef _configValues_h
#define _configValues_h

#include <map>
#include "ConfigParser.h"

namespace config
{
    struct cmp_str
    {
       bool operator()(char const *a, char const *b)
       {
          return std::strcmp(a, b) < 0;
       }
    };

    std::map<char*, char*, cmp_str> configValues;
}

#endif
