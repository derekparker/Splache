#ifndef HTTPPROCESSOR_H
#define HTTPPROCESSOR_H

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "SocketException.h"
#include "Constants.h"
#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <algorithm>

class HttpProcessor{
  //request:     Pointer to the request we got from the client
  //siteroot:    String representing the root of the site.
  //defaultPage: The default file the processor will look for 
  //             if the request specifies a directory
  //             dynamically allocated
  const HttpRequest* request;
  const char* siteroot;
  char* defaultPage;

  //Get the filename specified by the request
  //Returns a pointer to a new string. 
  //RETURN VALUE MUST BE FREED.
  char* getFilename(const char* requestFile) const;

  //Get the file extension of a file
  //DONT FREE! All we're really doing
  //is getting a pointer to some place
  //within the pathString
  char* getFileExtension(char* pathString);

 public:
  HttpProcessor();
  HttpProcessor(const HttpRequest &request, const char* site); //Request from client, site root
  ~HttpProcessor();

  //Set the default page
  void setDefaultPage(const char* defaultPage);

  //Generate a response object to send to the client
  void makeResponse(HttpResponse &response);

  //creates an error response when something goes wrong
  void makeErrorResponse(int status, HttpResponse &response);
};

#endif
