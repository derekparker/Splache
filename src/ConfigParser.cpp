/**  
 *  ConfigParser.h
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "ConfigParser.h"

ConfigParser::ConfigParser()
{
  config.open(PATH_TO_CONFIG, std::ifstream::in);
}
ConfigParser::~ConfigParser()
{
    config.close();
}

void ConfigParser::parseConfigString(
    std::map<std::string, std::string>& configMap, 
    std::string configString)
{
    std::stringstream configStream(
        configString, 
        std::stringstream::in | std::stringstream::out);

    parseStream(configMap, (std::istream*)&configStream);
}

void ConfigParser::parseStream(
    std::map<std::string, std::string>& configMap, 
    std::istream *stream)
{
    while ( stream->good() )
    {
        ch = stream->peek();
        if (ch != '#' && ch != '\n' && ch != (char)0)
        {
            stream->getline(buf, sizeof(buf));
            sscanf(buf, "%1024s %*s %1024s", key, val);
            if(strstr(val,"{") != NULL)
            {
                char *valend = val;
                while(strstr(val,"}") == NULL)
                {  
                    while(*++valend);
                    valend[0] = 13;
                    valend[1] = 10;
                    valend += 2;
                    stream->getline(valend,1024);
                    //sscanf(buf,"%1024s",valend);
                }
            }
            configMap[key] = val;
        }
        else
        {
            stream->ignore(sizeof(buf),'\n');
        }
    }
}

void ConfigParser::parseConfigFile(std::map<std::string, std::string>& configMap)
{
    if(config.is_open())
        parseStream(configMap, (std::istream*)&config);
    else
    {
        configMap["GOOD_CONFIG"] = "false";
        //configMap["TRAFFIC_VERBOSE"] = "true";
        //configMap["ERROR_VERBOSE"] = "true";
        std::cout << "Failed to open config file: "<< PATH_TO_CONFIG << std::endl;
    }
}
