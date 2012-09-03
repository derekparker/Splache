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
  if ( config.is_open() )
    {
      while ( config.good() )
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
	}
    }
  else 
  {
      configMap["GOOD_CONFIG"] = "false";
      configMap["TRAFFIC_VERBOSE"] = "true";
      configMap["ERROR_VERBOSE"] = "true";
      std::cout << "Failed to open config file: "<< PATH_TO_CONFIG << std::endl;
  }
}
