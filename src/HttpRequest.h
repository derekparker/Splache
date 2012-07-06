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
  void getHeaders(std::map<char*, char*>*, char*);
 public:
  char* method;
  char* file;
  char* host;
  std::map<char*,char*> *HTTP_headers;
  HttpRequest(){ HTTP_headers = NULL;}
  ~HttpRequest();
  HttpRequest(char* buffer);
  void setRequest(char* buffer);
};

#endif
