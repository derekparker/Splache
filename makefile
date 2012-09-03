CXX = g++ -ggdb -std=c++11
BINNAME = Splache
LINKS= -lpthread
OBJ = 	object/Splache.o \
	object/Socket.o \
	object/HttpResponse.o \
	object/HttpRequest.o \
	object/ServerSocket.o \
	object/Log.o \
	object/GeneralException.o \
	object/HttpProcessor.o \
	object/Worker.o \
	object/ConfigParser.o \
	object/FileHandler.o \
	object/ConfigValues.o \
	object/run.o \
	object/Helper.o

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

object/Splache.o : src/Splache.h src/Splache.cpp src/ConfigParser.h src/ConfigParser.cpp src/Socket.h src/HttpResponse.h src/HttpRequest.h src/ServerSocket.h src/SocketException.h src/Log.h src/ConfigValues.h src/HttpProcessor.h src/Worker.h src/run.h
	$(CXX) -c src/Splache.cpp -o object/Splache.o

object/Socket.o : src/Socket.h src/Socket.cpp
	$(CXX) -c src/Socket.cpp -o object/Socket.o

object/Log.o : src/Log.h src/Log.cpp
	$(CXX) -c src/Log.cpp -o object/Log.o

object/HttpResponse.o : src/HttpResponse.h src/HttpResponse.cpp src/Constants.h
	$(CXX) -c src/HttpResponse.cpp -o object/HttpResponse.o

object/HttpRequest.o : src/HttpRequest.h src/HttpRequest.cpp src/HttpException.h src/Helper.h
	$(CXX) -c src/HttpRequest.cpp -o object/HttpRequest.o

object/ServerSocket.o : src/ServerSocket.h src/ServerSocket.cpp src/Socket.h src/HttpRequest.h src/HttpResponse.h src/SocketException.h
	$(CXX) -c src/ServerSocket.cpp -o object/ServerSocket.o

object/HttpProcessor.o : src/HttpProcessor.h src/HttpProcessor.cpp src/HttpRequest.h src/HttpResponse.h src/Constants.h src/FileHandler.h
	$(CXX) -c src/HttpProcessor.cpp -o object/HttpProcessor.o

object/Worker.o : src/Worker.h src/Worker.cpp src/HttpResponse.h src/HttpRequest.h src/HttpProcessor.h src/Socket.h src/ServerSocket.h src/SocketException.h src/HttpException.h src/ConfigValues.h src/Log.h src/ConfigParser.h
	$(CXX) -c src/Worker.cpp -o object/Worker.o

object/GeneralException.o: src/GeneralException.h src/GeneralException.cpp
	$(CXX) -c src/GeneralException.cpp -o object/GeneralException.o

object/ConfigParser.o : src/ConfigParser.h src/ConfigParser.cpp src/ConfigValues.h
	$(CXX) -c src/ConfigParser.cpp -o object/ConfigParser.o

object/FileHandler.o : src/FileHandler.h src/FileHandler.cpp
	$(CXX) -c src/FileHandler.cpp -o object/FileHandler.o

object/ConfigValues.o : src/ConfigValues.h src/ConfigValues.cpp
	$(CXX) -c src/ConfigValues.cpp -o object/ConfigValues.o

object/run.o : src/run.h src/run.cpp
	$(CXX) -c src/run.cpp -o object/run.o

object/Helper.o : src/Helper.h src/Helper.cpp
	$(CXX) -c src/Helper.cpp -o object/Helper.o
