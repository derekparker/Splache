#include "Worker.h"

Worker::Worker(ServerSocket* listening_socket, Log* trafficLog, Log* errorLog)
{
  server_socket = listening_socket;
  trafficLogger = trafficLog;
  errorLogger   = errorLog;
  shouldRun     = true;
}

void Worker::run()
{
  try
    {
      while(shouldRun)
	{
	  ServerSocket socket;
	  server_socket->accept(&socket);
	  
	  //supportsKeepalive will be configurable.
	  bool open = true;
	  bool supportsKeepalive = true;
	  while(open)
	    {
	      open = processConnection(socket);
	      if(!supportsKeepalive)
		break;
	    }
	  socket.self_close();
	}
    }
  catch(SocketException *e)
    {
      e->logExceptionToFile(*errorLogger);
      delete(e);
    }
}

bool Worker::processConnection(ServerSocket &socket)
{
  //The three objects we'll be using to handle requests
  HttpRequest request   = HttpRequest();
  HttpResponse response = HttpResponse();
  HttpProcessor processor;
  bool open;
  
  try{
    //Read into the request
    socket >> &request;
    
    //The request won't be valid if the connection times out.
    //Otherwise process the request
    if(!request.isValid())
      return false;
      	
    //This will come from the configuration eventually.
    processor = HttpProcessor(request, config::configValues["WWW_ROOT"].c_str());//(char*)"/home/kyle/Documents/CodeBase/www");
    processor.setDefaultPage((char*)"index.html");
    processor.makeResponse(response);
    
    //If the response is an error, then close the connection.
    if(response.errorResponse == true)
      open = false;
    else if( (*request.HTTP_headers)[std::string("connection")] == "keep-alive")
      open = true;
    else
      open = false;
    
    //Send the response
    socket << &response;
    
    ///Log the traffic
    *trafficLogger
      << trafficLogger->getDateTime()
      << " Remote: " << inet_ntoa(socket.remoteAddr().sin_addr)
      << " requested " << request.file << endl;
  
  }
  catch(HttpException *e)
    {
      //Log the error, close the connection.
      open = false;
      e->logExceptionToFile(*trafficLogger);
      processor.makeErrorResponse(400, response);
      socket<<&response;
      delete(e);
    }
  return open; 
}

void Worker::kill(){
  shouldRun = false;
}
