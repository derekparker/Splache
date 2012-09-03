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
#include "Helper.h"

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

class HttpRequest{
    //request:      The request string.
    //method:       The method of the request; GET, POST, etc.
    //file:         The filename requested.
    char* request;
    char* method;
    char* file;

    //Gets a map of the headers in the request.
    void getHeaders(std::map<std::string,std::string>*, char*);

public:
  
    //getMethod(): Accessor
    //getFile():   Accessor
    //HTTP_headers: Map of the headers in the request
    const char* getMethod() const;
    const char* getFile() const;
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
