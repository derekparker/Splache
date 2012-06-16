#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

class HttpResponse{
  //These are constant fields that do not need to be dynamic.
  const char* STATUS = "HTTP/1.1";
  const char* SERVER_HEADER = "Server: Splache/Prerelease (Linux)";
  char* appendMovingBuffer(char* buffer, char* stringToAppend);
  char* headers;
public:
  int statusCode;
  //MAKE SURE THESE ARE NULL TERMINATED!!!
  char* body;
  char* makeResponseBuffer();
  void sendResponse(int socket);
  void addHeader(char*);
};

#endif
