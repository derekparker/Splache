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
      	
        std::string *host = stringHelper::hostTrim((*request.HTTP_headers)[std::string("host")].c_str());
        
        std::string s = config::configValues[*host];
        
        if(s != "")
        {
            std::map<std::string, std::string> host;
            ConfigParser *parser = new ConfigParser;
            
            parser->parseConfigString(host, s);
            delete(parser);

            processor = HttpProcessor(request, host["WWW_ROOT"].c_str());
            processor.setDefaultPage(host["DEFAULT_PAGE"].c_str());
        }
        else
        {
            processor = HttpProcessor(request, config::configValues["WWW_ROOT"].c_str());
            processor.setDefaultPage(config::configValues["DEFAULT_PAGE"].c_str());
        }
        
        processor.makeResponse(response);
    
        //If the response is an error, then close the connection and log to traffic log.
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
            << " requested " << (*request.HTTP_headers)["host"] << " " << request.getFile() 
            << " Status: "<< response.getStatusAndCode()
            <<endl;
    
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
