/**  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

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
  char* appendMovingBuffer(char* buffer, char* stringToAppend, int length);
  char* headers;
  char* body;
  int contentLength;
public:
  ~HttpResponse();
  int statusCode;
  int makeResponseBuffer(char**);
  //void sendResponse(int socket);
  void addHeader(char*);
  void setBody(char*,int);
};

#endif
