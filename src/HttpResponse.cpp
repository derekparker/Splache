#include "HttpResponse.h"

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
  int length = strlen(STATUS) + strlen(SERVER_HEADER) + strlen(headers) + strlen(body) + 11;
  char* responseBuffer = (char*)malloc(length);
  char* movingBuffer = responseBuffer;
  char charStatusCode[4];
  sprintf(charStatusCode, "%d", statusCode);

  movingBuffer = appendMovingBuffer(movingBuffer,(char*)STATUS);
  movingBuffer = appendMovingBuffer(movingBuffer," ");
  movingBuffer = appendMovingBuffer(movingBuffer,charStatusCode);
  movingBuffer = appendMovingBuffer(movingBuffer,"\r\n");
  movingBuffer = appendMovingBuffer(movingBuffer,(char*)SERVER_HEADER);
  movingBuffer = appendMovingBuffer(movingBuffer,"\r\n");
  movingBuffer = appendMovingBuffer(movingBuffer,headers);
  movingBuffer = appendMovingBuffer(movingBuffer,"\r\n");
  movingBuffer = appendMovingBuffer(movingBuffer,body);

  return responseBuffer;
}

char* HttpResponse::appendMovingBuffer(char* buffer, char* stringToAppend){
  strcpy(buffer,stringToAppend);
  return buffer + strlen(stringToAppend);
}
