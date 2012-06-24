#include "HttpProcessor.h"

HttpProcessor::HttpProcessor()
{
  request = NULL;
  defaultPage = NULL;
}
HttpProcessor::~HttpProcessor()
{
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
  if(defaultPage != NULL)
    free(defaultPage);
  defaultPage = (char*)malloc(strlen(page) + 1);
  strcpy(defaultPage, page);
}

void HttpProcessor::makeResponse(HttpResponse &response)
{
    if(request == NULL)
      throw new SocketException("No request to process.");
    
    char* filepath = getFilename(request->file);
    char* fileExt = getFileExtension(filepath);

    FILE * file; //(filepath, std::ifstream::binary);
    file = fopen(filepath, "rb");
    if( file == NULL )
      {
	response = HttpResponse();
	char* body = (char*)"<html><head></head><body><H1>404</H1></body></html>";
	response.setBody(body, strlen(body));
	response.statusCode = 404;
	response.addHeader((char*)"Content-Type: text/html; charset=UTF-8");
	response.addHeader((char*)"Connection: close");
      }
    else
      {
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	char* fileBuff = (char*)malloc(size);

	fread(fileBuff, size, 1, file);
	fclose(file);
	
	//std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());	
	
	response = HttpResponse();
	response.setBody((char*)fileBuff,size);
	free(fileBuff);
	response.statusCode = 200;
	if(strcmp(fileExt,"jpg") == 0)
	  response.addHeader((char*)"Content-Type: image/jpg;");
	else
	  response.addHeader((char*)"Content-Type: text/html; charset=UTF-8");
	response.addHeader((char*)"Connection: close");
     }
    free(filepath);
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
