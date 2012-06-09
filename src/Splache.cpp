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
            ServerSocket new_sock;
            server.accept(new_sock);
            
            try {
                while (true) {
                    /* This will send data to the HttpRequest class */
                    new_sock >> foo; 
                    /* This will send data back to the client
                     using the HttpResponse class */
                    new_sock << bar;
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
