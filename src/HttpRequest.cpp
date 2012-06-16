#include "HttpRequest.h"

HttpRequest::HttpRequest(char* buffer){
  setRequest(buffer);
}

void HttpRequest::setRequest(char* buffer){
  request = (char*)malloc(strlen(buffer)+1);
  strcat(request,buffer);

  char* placeholder;

  method = request;
  file = cutString(method, (char*)" ");
  placeholder = cutString(file, (char*)" ");
  host = cutString(placeholder, (char*)"Host");
  host += 6;
  placeholder = cutString(host, (char*)"\r");
  

  /*
  char* placeholder = strstr(request, " ");
  placeholder[0] = 0;
  file = placeholder+1;
  placeholder = strstr(file, " ");
  placeholder[0] = 0;
  host = strstr(request, "Host");
  host += 6;
  placeholder = strstr(host,(char*)13);
  placeholder[0]=0;
  */
}

char* HttpRequest::cutString(char * inStr, char * cutBy)
{
  char* placeholder = strstr(inStr, cutBy);
  placeholder[0] = 0;
  return placeholder+1;
}
