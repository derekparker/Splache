#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

class HttpResponse{
  //These are constant fields that do not need to be dynamic.
  const char* STATUS = "HTTP/1.1";
  const char* SERVER_HEADER = "Server: Splache/Prerelease (Linux)";
  char* makeResponseBuffer();
  void appendMovingBuffer(char* buffer, char* stringToAppend);
public:
  int statusCode;
  //MAKE SURE THESE ARE NULL TERMINATED!!!
  char* headers;
  char* body;

  void sendResponse(int socket);

};

#endif
