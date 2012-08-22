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

void ConfigParser::parseConfigFile(std::map<std::string, std::string>& configMap)
{
  while ( !config.eof() )
    {
      ch = config.peek();
      if (ch != '#' && ch != '\n' && ch != (char)0)
        {
	  config.getline(buf, sizeof(buf));
	  sscanf(buf, "%1024s %*s %1024s", key, val);
	  configMap[key] = val;
        }
      else
	{
	  config.ignore(sizeof(buf),'\n');
	}
      //ch = config.peek();
      //while(ch==' ' && ch=='\n'){
      //    config.ignore(sizeof(buf),'\n');
      //    ch = config.peek();
      ////}
    }
}
