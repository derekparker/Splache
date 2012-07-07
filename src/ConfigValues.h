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
#include <string.h>

namespace config
{
    struct cmp_str
    {
       bool operator()(const char *a, const char *b)
       {
          return strcmp(a, b) < 0;
       }
    };

    std::map<char*, char*, cmp_str> configValues;
}

#endif
