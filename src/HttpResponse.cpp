#include "HttpResponse.h"

HttpResponse::~HttpResponse(){
  if(headers != NULL)
    free(headers);
  if(body != NULL)
    free(body);
}

void HttpResponse::sendResponse(int socket){
  char* responseBuffer = makeResponseBuffer();
  //send responseBuffer 
  //I don't know how we're doing sockets yet, so 
  //I'll leave this in pseudocode for now
  printf("%s",responseBuffer);
  free(responseBuffer);
}

char* HttpResponse::makeResponseBuffer(){
  //+11 : 3 for status code, 6 for three newlines, one for a space, and one for null term. 
  int length = strlen(STATUS) + strlen(SERVER_HEADER) + strlen(headers) + strlen(body) + 13;
  char* responseBuffer = (char*)malloc(length);
  char* movingBuffer = responseBuffer;
  char charStatusCode[4];
  sprintf(charStatusCode, "%d", statusCode);

  movingBuffer = appendMovingBuffer(movingBuffer,(char*)STATUS);
  movingBuffer = appendMovingBuffer(movingBuffer,(char *)" ");
  movingBuffer = appendMovingBuffer(movingBuffer,charStatusCode);
  movingBuffer = appendMovingBuffer(movingBuffer,(char *)"\r\n");
  movingBuffer = appendMovingBuffer(movingBuffer,(char*)SERVER_HEADER);
  movingBuffer = appendMovingBuffer(movingBuffer,(char *)"\r\n");
  movingBuffer = appendMovingBuffer(movingBuffer,headers);
  movingBuffer = appendMovingBuffer(movingBuffer,(char *)"\r\n\r\n");
  movingBuffer = appendMovingBuffer(movingBuffer,body);

  return responseBuffer;
}

char* HttpResponse::appendMovingBuffer(char* buffer, char* stringToAppend){
  strcpy(buffer,stringToAppend);
  return buffer + strlen(stringToAppend);
}

void HttpResponse::addHeader(char* newHeader){
  int length;
  if(headers == NULL)
    {
      length = strlen(newHeader)+1;
      headers = (char*)malloc(length);
      strcpy(headers,newHeader);
    }
  else
    {
      length = strlen(headers) + strlen(newHeader) + 3;
      char* buff = (char*)malloc(length);
      strcpy(buff, headers);
      strcat(buff, (char*)"\r\n");
      strcat(buff, newHeader);
      free(headers);
      headers = buff;
    }
  
}

void HttpResponse::setBody(char* newBody){
  if(body != NULL)
    free(body);
  body = (char*) malloc(strlen(newBody)+1);
  strcpy(body,newBody);
  return;
}
