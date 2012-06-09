#include "HttpRequest.h"

HttpRequest::HttpRequest(char* buffer){
  setRequest(buffer);
}

void HttpRequest::setRequest(char* buffer){
  request = malloc(strlen(buffer)+1);
  strcat(request,buffer);
  method = request;
  char* placeholder = strstr(request, " ");
  placeholder[0] = 0;
  file = space+1;
  host = strstr(request, "Host");
  host += 6;
  placeholder = strstr(host,13);
  placeholder[0]=0;

}
