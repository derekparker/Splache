/**
 *  configValues.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#ifndef _configValues_h
#define _configValues_h

#include <map>
#include <string.h>
#include <string>

namespace config
{
  /*
    struct cmp_str
    {
       bool operator()(const char *a, const char *b)
       {
          return strcmp(a, b) < 0;
       }
    };
  */
  
  //Had to do this, otherwise each .o file had its own instance of "configValues"
  //configValues is actually declared in configValues.cpp.
    extern std::map<std::string, std::string> configValues;
}

#endif
