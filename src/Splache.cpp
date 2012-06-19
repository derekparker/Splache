/**
 *  Splache.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "Splache.h"

int main(int argc, char* argv[]) 
{
    try 
    {
        ServerSocket server(30000);
        ServerSocket sock;
        while (true) 
        {
            server.accept(sock);
            
            try 
            {
                /* This will send data to the HttpRequest class */
                HttpRequest request;
                HttpResponse response = HttpResponse();
                response.setBody((char*)"<html><head></head><body><H1>Hello, World!</H1><br />This message courtesy of<br/>Derek Parker & Kyle Nusbaum</body></html>");
                response.statusCode = 200;
                response.addHeader((char*)"Content-Type: text/html; charset=UTF-8");
                response.addHeader((char*)"Connection: close");
                sock >> &request; 
              
                //PROCESS REQUEST >> RESPONSE//
	      
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
        Log logger(PATH_TO_LOGFILE); // PATH_TO_LOGFILE will be replaced with a configparser class member <map>
        e.logExceptionToFile(logger);
        delete logger;
    }
    
    return 0;
}
