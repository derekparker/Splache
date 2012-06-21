/**  
 *  ConfigParser.h
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "ConfigParser.h"

ConfigParser::ConfigParser()
{
    ifstream config(PATH_TO_CONFIG);
}
ConfigParser:~ConfigParser()
{
    config.close();
}

ConfigParser::parseConfigFile(map<std::string, std::string>& configMap)
{
    while ( !config.eof() )
    {
        ch = config.get();
        if (ch != '#' && ch != '\n')
        {
            config.getline(buf, sizeof(buf));
            sscanf(buf, "%s %*s %s", key, val);
            configMap[key] = val;
        }
        config.ignore(sizeof(buf),'\n');
        ch = config.peek();
        while(ch==' ' && ch=='\n'){
            config.ignore(sizeof(buf),'\n');
            ch = config.peek();
        }
    }
}
