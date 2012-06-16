//
//  Splache.cpp
//  
//
//  Created by Derek Parker and Kyle Nusbaum on 6/5/12.
//  Copyright (c) 2012 Splache. All rights reserved.
//

#include "Splache.h"

int main(int argc, char* argv[]) {
    try {
        ServerSocket server(30000);
        
        while (true) {
            ServerSocket sock;
            server.accept(sock);
            
            try {
                while (true) {
                    /* This will send data to the HttpRequest class */
		    HttpRequest request;
		    HttpResponse response = HttpResponse();
		    response.body = (char*)"<html><head></head><body><H1>Hello, World!</H1></body></html>";
		    response.statusCode = 200;
		    response.addHeader((char*)"Content-Type: text/html; charset=UTF-8");
		    response.addHeader((char*)"Connection: close");
		    sock >> &request; 
                    
		    //PROCESS REQUEST >> RESPONSE//
		    
		    /* This will send data back to the client
                     using the HttpResponse class */
                    sock << &response;
                }
            }
            catch (SocketException&) {}
        }
    }
    
    catch (SocketException& e) {
        std::cout << e.description(); // This will change to log to a file.
    }
    
    return 0;
}
