#include <string.h>

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

class HttpRequest{
  char* request;
 public:
  char* method;
  char* file;
  char* host;
  HttpRequest();
  HttpRequest(char* buffer);
  void setRequest(char* buffer);

};

#endif
