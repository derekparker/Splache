#include "HttpRequest.h"

HttpRequest::HttpRequest(char* buffer){
  setRequest(buffer);
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
  cutString(host, (char*)"\r");
}

char* HttpRequest::cutString(char * inStr, char * cutBy)
{
  char* placeholder = strstr(inStr, cutBy);
  placeholder[0] = 0;
  return placeholder+1;
}
