#include "FileHandler.h"

char* FileHandler::getFile(const char* filepath)
{
  //This is where we'll bring access control, caching, and CGI/Scripting in.
  //That way, filetype and location will be transparent to HttpProcessor. 
  //It will always only handle image/html/etc. buffers. No file IO or scripting.

  //Get file
  FILE * file;
  file = fopen(filepath, "rb");

  if( file == NULL )
    {
      return NULL;
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
      size = ftell(file);
      rewind(file);
      
      //read the file into the buffer
      char* fileBuff = (char*)malloc(size);
      fread(fileBuff, size, 1, file);
      fclose(file);
      return fileBuff;
    }
      /*
	End If
      */
      
}

//I don't want to deal with this one yet.
/*
static const bool FileHandler::putFile(const char* filepath, const char* filebuffer)
{
  
}
*/
