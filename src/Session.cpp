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
	    
		//If the browser client supports persistent session, keep the connection alive.
		if( (*request.HTTP_headers)[std::string("connection")] == "keep-alive")
		  open = true;
		else
		  open = false;

		///Log the traffic
		*trafficLogger
		  << trafficLogger->getDateTime()
		  << " Remote: " << inet_ntoa(socket->remoteAddr().sin_addr)
		  << " requested " << request.file << endl;
		
		//This will come from the configuration eventually.
		processor = HttpProcessor(request, (char*)"/home/kyle/Documents/CodeBase/www");
		processor.setDefaultPage((char*)"index.html");
		processor.makeResponse(response);
		
		//If the response is an error, then close the connection.
		if(response.errorResponse == true)
		  open = false;
		
		//Send the response
		*socket << &response;
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
