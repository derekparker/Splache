/**  
 *  ConfigParser.h
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#ifndef _ConfigParser_h
#define _ConfigParser_h
#include <map>
#include <string>

/**
 * Class to parse through the config file and
 * set a map with key/value information based
 * on what is set in the config file.
 *
 * Definitely not finished, I will flesh out
 * the methods tomorrow, and determine the
 * best way to figure out the relative path
 * to the config file.
 */

class ConfigParser
{
private:
    map<std::string, std::string> config;
    const char* PATH_TO_CONFIG = ""; // Going to change this based off of a relative path to config file.
    
public:
    ConfigParser();
    ~ConfigParser();
    
    void parseConfigFile();
    
    std::string getConfigValueByKey(std::string key);
}

#endif
