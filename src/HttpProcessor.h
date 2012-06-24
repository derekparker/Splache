#ifndef HTTPPROCESSOR_H
#define HTTPPROCESSOR_H

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "SocketException.h"
#include <iostream>
#include <fstream>

class HttpProcessor{
  const HttpRequest* request;
  const char* siteroot;
  char* defaultPage;
 public:
  HttpProcessor();
  HttpProcessor(const HttpRequest &request, char* site);
  ~HttpProcessor();
  void setDefaultPage(char* defaultPage);
  void makeResponse(HttpResponse &response);
  char* getFilename(char* requestFile);
  char* getFileExtension(char* pathString);

};

#endif
