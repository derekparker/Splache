#include "Session.h"

Session::Session(ServerSocket* accepted_socket, Log* trafficLog, Log* errorLog)
{
  socket = accepted_socket;
  trafficLogger = trafficLog;
  errorLogger = errorLog;
}

void Session::run()
{
  try
    {
      bool open = true;
      while(open)
	{
	  HttpRequest request = HttpRequest();
	  HttpResponse response = HttpResponse();
	  HttpProcessor processor = HttpProcessor();
	  try{
	    *socket >> &request;
	    if(!request.isValid())
	      {
		open = false;
		printf("Please?");
	      }
	    else
	      {
	    
		if( (*request.HTTP_headers)[std::string("connection")] == "keep-alive")
		  open = true;
		else
		  open = false;
		
		*trafficLogger
		  << trafficLogger->getDateTime()
		  << " Remote: " << inet_ntoa(socket->remoteAddr().sin_addr)
		  << " requested " << request.file << endl;
		
		processor = HttpProcessor(request, (char*)"/home/kyle/Documents/CodeBase/www");
		processor.setDefaultPage((char*)"index.html");
		processor.makeResponse(response);
		
		if(response.errorResponse == true)
		  open = false;
		
		*socket << &response;
	      }
	  }
	  catch(HttpException *e)
	    {
	      open = false;
	      e->logExceptionToFile(*trafficLogger);
	      processor.makeErrorResponse(400, response);
	      *socket<<&response;
	      delete(e);
	    }
	}
      socket->self_close();
    }
  catch(SocketException *e)
    {
      e->logExceptionToFile(*errorLogger);
      delete(e);
    }
}
