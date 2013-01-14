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
#include <sstream>
#include <string.h>

class ConfigParser
{
private:
    static constexpr char* PATH_TO_CONFIG = (char*)"conf/Splache.conf";
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
    void parseConfigString(
        std::map<std::string, std::string>& configMap,
        std::string configString);
    void parseStream(
        std::map<std::string, std::string>& configMap,
        std::istream *stream);

};
#endif
