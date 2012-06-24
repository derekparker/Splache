/**  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "HttpResponse.h"

HttpResponse::HttpResponse(){
  headers = NULL;
  body = NULL;
  response = NULL;
  contentLength = 0;
}

HttpResponse::~HttpResponse(){
  if(headers != NULL)
    free(headers);
  if(body != NULL)
    free(body);
  if(response != NULL)
    free(response);
}
/*
void HttpResponse::sendResponse(int socket){
  char* responseBuffer = makeResponseBuffer();
  //send responseBuffer 
  //I don't know how we're doing sockets yet, so 
  //I'll leave this in pseudocode for now
  printf("%s",responseBuffer);
  free(responseBuffer);
}
*/
void HttpResponse::makeResponseBuffer(){

  contentLength = strlen(STATUS) + strlen(SERVER_HEADER) + strlen(headers) + bodyLength + 12;
  response = (char*)malloc(contentLength);
  char* movingBuffer = response;
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
  movingBuffer = appendMovingBuffer(movingBuffer,body,bodyLength);
}

char* HttpResponse::appendMovingBuffer(char* buffer, char* stringToAppend){
  strcpy(buffer,stringToAppend);
  return buffer + strlen(stringToAppend);
}

char* HttpResponse::appendMovingBuffer(char* buffer, char* stringToAppend, int length)
{
  memcpy(buffer, stringToAppend, length);
  return buffer + length;
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

void HttpResponse::setBody(char* newBody, int bodyLength){
  if(body != NULL)
    free(body);
  //body = (char*) malloc(strlen(newBody)+1);
  this->bodyLength = bodyLength;
  body = (char*) malloc(bodyLength);
  memcpy(body, newBody, bodyLength);
  return;
}
