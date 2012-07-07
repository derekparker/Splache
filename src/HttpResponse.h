/**  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"

#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

class HttpResponse{
  //These are constant fields that do not need to be dynamic.
  const char* STATUS = "HTTP/1.1";
  const char* SERVER_HEADER = "Server: TESTING (Linux)";
  char* appendMovingBuffer(char* buffer, const char* stringToAppend);
  char* appendMovingBuffer(char* buffer, const char* stringToAppend, int length);
  const char* statusAndCode;
  char* headers;
  char* body;
  int bodyLength;
  char* response;
 public:
  HttpResponse();
  ~HttpResponse();
  bool errorResponse;
  void makeResponseBuffer();
  void addHeader(char*);
  void setBody(char*,int);
  const char* Response(){return response;}
  int ContentLength();
  const int BodyLength(){return bodyLength;}
  void SetStatusCode(int statusCode);
};

#endif
