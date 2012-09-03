#include "HttpProcessor.h"

HttpProcessor::HttpProcessor()
{
  request = NULL;
  defaultPage = NULL;
}
HttpProcessor::~HttpProcessor()
{
  //make sure we don't leak the defaultPage
  if(defaultPage != NULL)
    free(defaultPage);
}

HttpProcessor::HttpProcessor(const HttpRequest &request, const char* site)
{
  this->request = &request;
  siteroot = site;
  defaultPage = NULL;
}

void HttpProcessor::setDefaultPage(const char* page)
{
  //make sure we don't leak the defaultPage
  if(defaultPage != NULL)
    free(defaultPage);
  defaultPage = (char*)malloc(strlen(page) + 1);
  strcpy(defaultPage, page);
}

void HttpProcessor::makeErrorResponse(int status, HttpResponse &response)
{
  //We'll make errors customizable at some point. For now this will do.
  response = HttpResponse();
  char* body = (char*)malloc(54);
  strcpy(body,"<html><head></head><body><H1>Error</H1></body></html>");
  response.setBody(body, strlen(body));
  response.SetStatusCode(status);
  response.addHeader((char*)"Content-Type: text/html; charset=UTF-8");
  response.addHeader((char*)"Connection: close");
  response.errorResponse = true;
}

void HttpProcessor::makeResponse(HttpResponse &response)
{
    if(request == NULL)
      throw new SocketException("No request to process.");

    FileHandler file = FileHandler();
    char* filepath = getFilename(request->getFile());
    const char* fileExt = getFileExtension(filepath);
    char* fileBuff = file.getFile(filepath);
    int size = file.size;

    free(filepath);

    if(fileBuff == NULL)
      {
	makeErrorResponse(404, response);
      }
    else
      {
	//initialize the response, set body and status
	response = HttpResponse();
	response.setBody((char*)fileBuff,size);
	//Don't free it. response object frees it on destruction.
	//free(fileBuff);
	response.SetStatusCode(200);

	//Get the Mimetype
	const char* mimeType = Constants::MIME_TYPES.find(fileExt)->second.c_str();

	if( mimeType != "")
	  {
	    char contentType[50];
	    strcpy(contentType, (char*)"Content-Type: ");
	    strcat(contentType, mimeType);
	    response.addHeader(contentType);
	  }
	

	{
	  //JUST CHANGED from the commented below. If clients start acting funny,
	  //Try checking this out.
	  if ((*request->HTTP_headers)[std::string("Connection")] == "keep-alive")
	    response.addHeader((char*)"Connection: keep-alive");
	  else
	    response.addHeader((char*)"Connection: close");
	  
	  //if((*request->HTTP_headers)[std::string("connection")] == "close")
	  //  response.addHeader((char*)"Connection: close");
	}
	
	//Set Content-Length header. Sometimes we won't need this.
	//I'll have to read more about when we need this.
	int contentLength = response.BodyLength();
	char contentLengthstr[50];
	sprintf(contentLengthstr,"Content-Length: %d",contentLength);
	response.addHeader(contentLengthstr);
      }
    
}

char* HttpProcessor::getFilename(const char* requestFile) const
{
  const char* finalchar = requestFile + strlen(requestFile)-1;
  char* filename;
  if(strcmp(finalchar,"/") == 0)
    {
      filename = (char*)malloc(strlen(requestFile) + strlen(defaultPage) + 1);
      strcpy(filename, requestFile);
      strcat(filename, defaultPage);
    }
  else
    {
      filename = (char*)malloc(strlen(requestFile)+1);
      strcpy(filename, requestFile);
    }
  
  char *filepath = (char*)malloc(strlen(siteroot) + strlen(filename) + 1);
  strcpy(filepath, siteroot);
  strcat(filepath, filename);
  free(filename);
  return filepath;
}

char* HttpProcessor::getFileExtension(char* pathString)
{
  for(int i = strlen(pathString); i >= 0;  i--)
      if(pathString[i] == '.')
	{
	  char* extensionLoc = pathString + i + 1;
	  return extensionLoc;
	}
      else if(pathString[i] == '/')
	  return NULL;

  return NULL;
}
