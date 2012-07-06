/**  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <string>

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

class HttpRequest{
  char* request;
  char* cutString(char*, char*);
  void getHeaders(std::map<std::string,std::string>*, char*);
 public:
  char* method;
  char* file;
  char* host;
  std::map<std::string,std::string>* HTTP_headers;
  HttpRequest(){} //HTTP_headers = NULL;}
  ~HttpRequest();
  HttpRequest(char* buffer);
  void setRequest(char* buffer);
};

#endif
