CXX = g++ -ggdb -std=c++11
BINNAME = Splache
LINKS= -lpthread
OBJ = object/Splache.o \
	object/Socket.o \
	object/HttpResponse.o \
	object/HttpRequest.o \
	object/ServerSocket.o \
	object/Log.o \
	object/GeneralException.o \
	object/HttpProcessor.o \
	object/Session.o


all: splache

pre-build:
	-@mkdir bin
	-@mkdir object

clean:
	-@rm -R object
	-@rm -R bin
	-@rm $(BINNAME)

splache : pre-build $(OBJ)
	$(CXX) $(LINKS) -o bin/$(BINNAME) $(OBJ)

	-@rm $(BINNAME)
	ln -s bin/$(BINNAME) $(BINNAME)

object/Splache.o : src/Splache.h src/Splache.cpp src/Socket.h src/HttpResponse.h src/HttpRequest.h src/ServerSocket.h src/SocketException.h src/Log.h src/ConfigValues.h src/HttpProcessor.h src/Session.h
	$(CXX) -c src/Splache.cpp -o object/Splache.o

object/Socket.o : src/Socket.h src/Socket.cpp
	$(CXX) -c src/Socket.cpp -o object/Socket.o
    
object/Log.o : src/Log.h src/Log.cpp
	$(CXX) -c src/Log.cpp -o object/Log.o

object/HttpResponse.o : src/HttpResponse.h src/HttpResponse.cpp src/Constants.h
	$(CXX) -c src/HttpResponse.cpp -o object/HttpResponse.o

object/HttpRequest.o : src/HttpRequest.h src/HttpRequest.cpp src/HttpException.h
	$(CXX) -c src/HttpRequest.cpp -o object/HttpRequest.o

object/ServerSocket.o : src/ServerSocket.h src/ServerSocket.cpp src/Socket.h src/HttpRequest.h src/HttpResponse.h src/SocketException.h
	$(CXX) -c src/ServerSocket.cpp -o object/ServerSocket.o

object/HttpProcessor.o : src/HttpProcessor.h src/HttpProcessor.cpp src/HttpRequest.h src/HttpResponse.h src/Constants.h
	$(CXX) -c src/HttpProcessor.cpp -o object/HttpProcessor.o

object/Session.o : src/Session.h src/Session.cpp src/HttpResponse.h src/HttpRequest.h src/HttpProcessor.h src/Socket.h src/ServerSocket.h src/SocketException.h src/HttpException.h src/ConfigValues.h src/Log.h
	$(CXX) -c src/Session.cpp -o object/Session.o

object/GeneralException.o: src/GeneralException.h src/GeneralException.cpp
	$(CXX) -c src/GeneralException.cpp -o object/GeneralException.o
