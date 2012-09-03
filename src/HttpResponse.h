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
  //STATUS:        Not really a status, just the protocol version
  //SERVER_HEADER: The server header we'll pass to the client
  //statusAndCode: The status numeric and english code (200 OK)
  //headers:       The string of headers 
  //body:          The string holding the response body
  //bodyLength:    The length of the body
  //response:      The completed response string
  const char* STATUS = "HTTP/1.1";
  const char* SERVER_HEADER = "Server: Splache/Pre-Release (Linux)";
  const char* statusAndCode;
  char* headers;
  char* body;
  int bodyLength;
  char* response;

  //appendMovingBuffer writes to a buffer and returns a pointer
  //to the char after the final one it writes.
  //length parameter will cause the method to write past any null it finds.
  char* appendMovingBuffer(char* buffer, const char* stringToAppend);
  char* appendMovingBuffer(char* buffer, const char* stringToAppend, int length);

 public:
  HttpResponse();
  ~HttpResponse();

  //errorResponse is a status that determines whether or not this
  //response is an error or not.
  bool errorResponse;

  //generate the response from members
  void makeResponseBuffer();

  //Add a header to the response
  void addHeader(char*);

  //Set the body. This needs to be deallocated at some point.
  //Make sure whatever char* you pass to is is dynamically allocated
  //and stays alive
  void setBody(char*,int);

  //accessor for response
  const char* Response(){return response;}

  //get the contentLength of the request
  int ContentLength();

  //accessor for bodyLength
  const int BodyLength(){return bodyLength;}

  //set the request status code
  void SetStatusCode(int statusCode);

  //Get status and code
  const char* getStatusAndCode();

};

#endif
