/**
 *  Splache.cpp
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#include "Splache.h"

/*TEMPORARY*/
//#include <sys/socket.h>
//#include <netinet/in.h>

static void daemonize();

int main(int argc, char* argv[]) 
{
  daemonize();
    try 
    {
        ServerSocket server(30000);
        ServerSocket sock;
	char* PATH_TO_TRAFFICLOG = "../logs/splache.traffic";
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
	        
		processor = HttpProcessor(request, "/home/kyle/Documents/CodeBase/www");
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

static void daemonize()
{
  pid_t pid;
  pid = fork();
  if(pid < 0)
    exit(-1);
  
  //If original process, exit.
  if(pid > 0)
    exit(0);

  //If we are executing this, we are the child process.
  //Change the file usermask.
  umask(0);
  
  //Create new group and make child the leader
  if(setsid() < 0)
    exit(1);
  
  //Change working directory. (Eventually pull this from config?)
  if(chdir("/") < 0)
    exit(1);

  //Redirect standard IO streams
  freopen("/dev/null/", "r", stdin);
  freopen("/dev/null/", "w", stdout);
  freopen("/dev/null/", "w", stderr);
  
}
