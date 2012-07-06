/**  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "HttpRequest.h"

HttpRequest::HttpRequest(char* buffer){
  setRequest(buffer);
  //HTTP_headers = NULL;
}

HttpRequest::~HttpRequest(){
  if(request != NULL)
    free(request);
}

void HttpRequest::setRequest(char* buffer){
  request = (char*)malloc(strlen(buffer)+1);
  strcpy(request,buffer);

  char* placeholder;

  method = request;
  file = cutString(method, (char*)" ");
  placeholder = cutString(file, (char*)" ");
  host = cutString(placeholder, (char*)"Host");
  host += 6;
  placeholder = cutString(host, (char*)"\r")+1;
  //printf("%s",placeholder);

  //if(HTTP_headers != NULL)
  //  delete(HTTP_headers);

  HTTP_headers = new std::map<std::string,std::string>();

  getHeaders(HTTP_headers, placeholder);
  /*
  std::map<std::string,std::string>::iterator iter;
  for(iter = HTTP_headers->begin(); iter != HTTP_headers->end(); iter++)
    {
      printf("%s is this: %s\n", iter->first.c_str(), iter->second.c_str());
    }
    /**/
}

char* HttpRequest::cutString(char * inStr, char * cutBy)
{
  char* placeholder = strstr(inStr, cutBy);
  placeholder[0] = 0;
  return placeholder+1;
}

void HttpRequest::getHeaders(std::map<std::string,std::string>* headerMap, char* headerList)
{
  char* colon = (char*)":";
  
  char* lineHead = headerList;
  char* valueHead;
  char* lineEnd;
  
  while(lineHead[0] != '\r')
    {
      valueHead = cutString(lineHead,colon)+1;
      lineEnd = cutString(valueHead,(char*)"\r")+1;
      (*headerMap)[std::string(lineHead)] = std::string(valueHead);
      lineHead = lineEnd;
    }
}


