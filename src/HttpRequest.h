/**  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <string>
#include <algorithm>
#include "HttpException.h"

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

class HttpRequest{
  //request:      The request string.
  char* request;

  //Cuts up a string you pass it based on a search parameter.
  //Finds the first instance of the search string, writes a
  //null terminator to the character at that index, and returns
  //a pointer to the second character.
  char* cutString(char*, char*);

  //Gets a map of the headers in the request.
  void getHeaders(std::map<std::string,std::string>*, char*);

 public:
  
  //method:       The method of the request; GET, POST, etc.
  //file:         The filename requested.
  //HTTP_headers: Map of the headers in the request
  char* method;
  char* file;
  std::map<std::string,std::string>* HTTP_headers;

  HttpRequest();
  ~HttpRequest();

  //Initializes and sets up the request
  HttpRequest(char* buffer);

  //Set up the request
  void setRequest(char* buffer);

  //Check if file or method is null
  bool isValid();
};

#endif
