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
      //supportsKeepalive will be 
      bool open = true;
      bool supportsKeepalive = true;
      while(open)
	{
	  //The three objects we'll be using to handle requests
	  HttpRequest request = HttpRequest();
	  HttpResponse response = HttpResponse();
	  HttpProcessor processor = HttpProcessor();
	  
	  try{
	    //Read into the request
	    *socket >> &request;
	    
	    //The request won't be valid if the connection times out.
	    //Otherwise process the request
	    if(!request.isValid())
	      {
		open = false;
	      }
	    else
	      {		
		//This will come from the configuration eventually.
		processor = HttpProcessor(request, (char*)"/home/kyle/Documents/CodeBase/www");
		processor.setDefaultPage((char*)"index.html");
		processor.makeResponse(response);
		
		//If the response is an error, then close the connection.
		//If we don't support keep-alive, we'll also definitely want to close the connection.
		if(response.errorResponse == true || !supportsKeepalive)
		  open = false;
		else if( (*request.HTTP_headers)[std::string("connection")] == "keep-alive")
		  open = true;
		else
		  open = false;
	
		//Send the response
		*socket << &response;

		///Log the traffic
		*trafficLogger
		  << trafficLogger->getDateTime()
		  << " Remote: " << inet_ntoa(socket->remoteAddr().sin_addr)
		  << " requested " << request.file << endl;
	      }
	    
	  }
	  catch(HttpException *e)
	    {
	      //Log the error, close the connection.
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
