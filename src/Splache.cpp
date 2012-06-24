/**
 *  Splache.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "Splache.h"

/*TEMPORARY*/
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) 
{
    try 
    {
        ServerSocket server(30000);
        ServerSocket sock;
	char* PATH_TO_TRAFFICLOG = "./logs/splache.traffic";
        Log logger(PATH_TO_TRAFFICLOG);

        while (true) 
        {
            server.accept(sock);            
            try 
            {
                /* This will send data to the HttpRequest class */
                HttpRequest request;
                HttpResponse response;
		HttpProcessor processor;

		sock >> &request;
		logger 
		  << logger.getDateTime() 
		  << " Remote: " << inet_ntoa(server.remoteAddr().sin_addr) 
		  << " requested " << request.file << endl;
	        
		processor = HttpProcessor(request, "/home/kyle/Documents/CodeBase/Splache/www");
		processor.setDefaultPage("index.html");
		processor.makeResponse(response);
		

                /* This will send data back to the client
                 using the HttpResponse class */
                sock << &response;
                server.close(sock);
            }
            catch (SocketException&) {}
        }
    }
    
    catch (SocketException& e) 
    {
      char* PATH_TO_LOGFILE = "./logs/splache.log";
        Log logger(PATH_TO_LOGFILE); 
	// PATH_TO_LOGFILE will be replaced with a configparser class member <map>
        e.logExceptionToFile(logger);
	printf("%s\n",e.message());
        //delete logger;
    }
    
    return 0;
}

