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

HttpProcessor::HttpProcessor(const HttpRequest &request, char* site)
{
  this->request = &request;
  siteroot = site;
  defaultPage = NULL;
}

void HttpProcessor::setDefaultPage(char* page)
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
  char* body = (char*)"<html><head></head><body><H1>Error</H1></body></html>";
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
    
    char* filepath = getFilename(request->file);
    char* fileExt = getFileExtension(filepath);
    
    //Get file
    FILE * file;
    file = fopen(filepath, "rb");
    free(filepath);

    if( file == NULL )
      {
	makeErrorResponse(404, response);
      }
    else
      {

	/*
	  TODO:
	  Check file extension against configuration.
	  IF the file matches an extension in the config,
	      Run CGI on file and get results.
	  ELSE
	      Do Following:
	*/
	
	//Get the filelength
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	//read the file into the buffer
	char* fileBuff = (char*)malloc(size);
	fread(fileBuff, size, 1, file);
	fclose(file);

	/*
	  End If
	 */


	//initialize the response, set body and status
	response = HttpResponse();
	response.setBody((char*)fileBuff,size);
	//free(fileBuff);
	response.SetStatusCode(200);

	//Get the Mimetype
	std::string mimeType = Constants::MIME_TYPES.find(fileExt)->first;

	if( mimeType != "")
	  {
	    char contentType[50];
	    strcpy(contentType, (char*)"Content-Type: ");
	    strcat(contentType, Constants::MIME_TYPES.find(fileExt)->second.c_str());
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

char* HttpProcessor::getFilename(char* requestFile)
{
  char* finalchar = requestFile + strlen(requestFile)-1;
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
