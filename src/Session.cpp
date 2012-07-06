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
	  *socket >> &request;
	  //std::string s = std::string("Connection");
	  //std::map<std::string,std::string> *headers = request.HTTP_headers;
	  //std::string s2 = (*headers)[s];
	  //printf("%s\n", (*request.HTTP_headers)[std::string("Connection")].c_str());
	  
	  //if( (*request.HTTP_headers)[std::string("Connection")] == "keep-alive")
	  //  open = true;
	  //else
	    open = false;

	  *trafficLogger
	    << trafficLogger->getDateTime()
	    << " Remote: " << inet_ntoa(socket->remoteAddr().sin_addr)
	    << " requested " << request.file << endl;
	  
	  processor = HttpProcessor(request, (char*)"/home/kyle/Documents/CodeBase/www");
	  processor.setDefaultPage((char*)"index.html");
	  processor.makeResponse(response);

	  //printf("%s\n",response.Response());

	  *socket << &response;
	}
      socket->self_close();
    }
  catch(SocketException& e)
    {
      e.logExceptionToFile(*errorLogger);
    }
}
