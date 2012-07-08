/**  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "HttpRequest.h"

HttpRequest::HttpRequest(char* buffer){
  setRequest(buffer);
  method = NULL;
  file = NULL;
  HTTP_headers = NULL;
}

HttpRequest::HttpRequest(){
  request = NULL;
  method = NULL;
  file = NULL;
  HTTP_headers = NULL;
}

HttpRequest::~HttpRequest(){
  if(request != NULL)
    free(request);
  if(HTTP_headers != NULL)
    delete(HTTP_headers);
}

bool HttpRequest::isValid(){
  if(method == NULL || file == NULL)
    return false;
  return true;
}

void HttpRequest::setRequest(char* buffer){
  request = (char*)malloc(strlen(buffer)+1);
  strcpy(request,buffer);

  if(HTTP_headers != NULL)
    delete(HTTP_headers);

  HTTP_headers = new std::map<std::string,std::string>();

  char* placeholder;

  //Method is at the beginning of the request
  method = request;

  //Cut the string at the end of the method, Where the file is. 
  //File string start is next char.
  file = cutString(method, (char*)" ");
  
  //If we couldn't get the file, this request is malformed.
  if((long)file == 0)
    throw new HttpException("Bad Request");

  //Cut the end of the file string
  placeholder = cutString(file, (char*)" ");
  
  //Jump to the next line, where the headers will be.
  placeholder = cutString(placeholder, (char*)"\r")+1;

  //If we couldn't get a newline, there are no headers.
  if((long)placeholder == 1)
    return;

  getHeaders(HTTP_headers, placeholder);

  //I'll leave this here for debugging.
  //Just prints out all headers we've gotten.
  
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
  if(placeholder != 0)
    {
      placeholder[0] = 0;
      placeholder++;
    }
  return placeholder;
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
      if((long)valueHead == 1)
	return;
      lineEnd = cutString(valueHead,(char*)"\r")+1;
      std::string s_line = std::string(lineHead);
      std::string s_value = std::string(valueHead);
      std::transform(s_line.begin(), s_line.end(), s_line.begin(), ::tolower);
      std::transform(s_value.begin(), s_value.end(), s_value.begin(), ::tolower);
      (*headerMap)[s_line] = s_value;
      lineHead = lineEnd;
    }
}


