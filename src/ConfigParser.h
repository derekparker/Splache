/**  
 *  ConfigParser.h
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#ifndef _ConfigParser_h
#define _ConfigParser_h
#include <map>
#include <string>
#include <iostream>
#include <fstream>

//#include "ConfigValues.h"

/**
 * Class to parse through the config file and
 * set a map with key/value information based
 * on what is set in the config file.
 *
 * Definitely not finished, I will flesh out
 * the methods tomorrow, and determine the
 * best way to figure out the relative path
 * to the config file.
 *
 */

//#define PATH_TO_CONFIG = "../conf/Splache.conf";

class ConfigParser
{
private:
    static constexpr char* PATH_TO_CONFIG = (char*)"../conf/Splache.conf";
    static const int MAX_SIZE = 1024; // 1023 for string + 1 for null terminator

    char buf[1024];
    char ch = ' ';
    char key[MAX_SIZE];
    char val[MAX_SIZE];
    std::ifstream config;
    
public:
    ConfigParser();
    ~ConfigParser();
    
    void parseConfigFile(std::map<std::string, std::string>& configMap);
};
#endif
