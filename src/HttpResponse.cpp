/**  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "HttpResponse.h"

HttpResponse::HttpResponse(){
  headers       = NULL;
  body          = NULL;
  response      = NULL;
  errorResponse = false;
}

HttpResponse::~HttpResponse(){
  //make sure we don't leak any memory
  if(headers != NULL)
    free(headers);
  if(body != NULL)
    free(body);
  if(response != NULL)
    free(response);
}

void HttpResponse::makeResponseBuffer(){
  
  response = (char*)malloc(ContentLength());
  char* movingBuffer = response;

  //Collect the response string
  movingBuffer = appendMovingBuffer(movingBuffer,(char*)STATUS);
  movingBuffer = appendMovingBuffer(movingBuffer,(char *)" ");
  movingBuffer = appendMovingBuffer(movingBuffer,statusAndCode);
  movingBuffer = appendMovingBuffer(movingBuffer,(char *)"\r\n");
  movingBuffer = appendMovingBuffer(movingBuffer,(char*)SERVER_HEADER);
  movingBuffer = appendMovingBuffer(movingBuffer,(char *)"\r\n");
  movingBuffer = appendMovingBuffer(movingBuffer,headers);
  movingBuffer = appendMovingBuffer(movingBuffer,(char *)"\r\n\r\n");
  movingBuffer = appendMovingBuffer(movingBuffer,body,bodyLength);
}

int HttpResponse::ContentLength(){
  return strlen(STATUS)+strlen(statusAndCode)+strlen(SERVER_HEADER)+strlen(headers)+bodyLength+9;
}

char* HttpResponse::appendMovingBuffer(char* buffer, const char* stringToAppend){
  strcpy(buffer,stringToAppend);
  return buffer + strlen(stringToAppend);
}

char* HttpResponse::appendMovingBuffer(char* buffer, const char* stringToAppend, int length)
{
  memcpy(buffer, stringToAppend, length);
  return buffer + length;
}

void HttpResponse::addHeader(char* newHeader){
  int length;
  if(headers == NULL)
    {
      length  = strlen(newHeader)+1;
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
  this->bodyLength = bodyLength;
  
  // using pointer rather than making a copy, for speed
  body = newBody;
  
  return;
}

void HttpResponse::SetStatusCode(const int statusCode)
{
  //Looks up the status code in the Constants namespace and sets it.
  statusAndCode = Constants::RESPONSE_CODES.find(statusCode)->second.c_str();
}

const char* HttpResponse::getStatusAndCode()
{
    return statusAndCode;
}
