#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

class HttpRequest{
  char* request;
  char* cutString(char*, char*);
 public:
  char* method;
  char* file;
  char* host;
  HttpRequest(){}
  HttpRequest(char* buffer);
  void setRequest(char* buffer);
};

#endif
