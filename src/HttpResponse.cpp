#include "HttpResponse.h"

void HttpResponse::sendResponse(int socket){
  char* responseBuffer = makeResponseBuffer();
  //send responseBuffer 
  //I don't know how we're doing sockets yet, so 
  //I'll leave this in pseudocode for now

  free(responseBuffer);
}

char* HttpResponse::makeResponseBuffer(){
  //Don't worry. I'll clean this way up before I move on. It's just helpful for keeping
  //track of how long the buffer needs to be. I'm not entirely sure it's correct yet, either.

  //Length of status plus space plus 3-digit code plus 2 char newline
  //plus length of headers plus 2 char newline plus length of body
  //plus space for new null term
  int length = strlen(STATUS) +1 +3+2 
    +(strlen(SERVER_HEADER)+2) + (strlen(headers)+2) + (strlen(body)) +1;
  char* responseBuffer = (char*)malloc(length);
  char* movingBuffer = responseBuffer;
  char newline[] = {13, 10, 0}; //CR LF
  char charStatusCode[4];
  sprintf(charStatusCode, "%d", statusCode);

  movingBuffer = appendMovingBuffer(movingBuffer,(char*)STATUS);
  movingBuffer = appendMovingBuffer(movingBuffer," ");
  movingBuffer = appendMovingBuffer(movingBuffer,charStatusCode);
  movingBuffer = appendMovingBuffer(movingBuffer,newline);
  movingBuffer = appendMovingBuffer(movingBuffer,(char*)SERVER_HEADER);
  movingBuffer = appendMovingBuffer(movingBuffer,newline);
  movingBuffer = appendMovingBuffer(movingBuffer,headers);
  movingBuffer = appendMovingBuffer(movingBuffer,newline);
  movingBuffer = appendMovingBuffer(movingBuffer,body);

  return responseBuffer;
}

char* HttpResponse::appendMovingBuffer(char* buffer, char* stringToAppend){
  strcpy(buffer,stringToAppend);
  return buffer + strlen(stringToAppend);
}
