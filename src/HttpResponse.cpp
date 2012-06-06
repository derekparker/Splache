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

  //Length of status minus null term plus space plus 3-digit code plus 2 char newline
  //plus length of headers minus null term plus 2 char newline plus length of body minus
  //null term plus space for new null term
  int length = strlen(STATUS) -1 +1 +3+2 
    +(strlen(headers)-1+2) + (strlen(body)-1) +1;
  char* responseBuffer = (char*)malloc(length);
  char* movingBuffer = responseBuffer;
  char* space = " ";
  char* newline = "00"; //CR LF

  newline[0] = 13;
  newline[1] = 10;

  char charStatusCode[4];
  sprintf(charStatusCode, "%d", statusCode);

  appendMovingBuffer(movingBuffer,(char*)STATUS);
  appendMovingBuffer(movingBuffer,space);
  appendMovingBuffer(movingBuffer,charStatusCode);
  appendMovingBuffer(movingBuffer,newline);
  appendMovingBuffer(movingBuffer,(char*)SERVER_HEADER);
  appendMovingBuffer(movingBuffer,newline);
  appendMovingBuffer(movingBuffer,headers);
  appendMovingBuffer(movingBuffer,newline);
  appendMovingBuffer(movingBuffer,body);

  free(space);
  free(newline);

  return responseBuffer;
}

void HttpResponse::appendMovingBuffer(char* buffer, char* stringToAppend){
  strcpy(buffer,stringToAppend);
  //Uint8 bufAdr = (Uint8)buffer;
  buffer += strlen(stringToAppend)-1;
}
