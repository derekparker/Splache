CXX = g++ -ggdb -std=c++11
BINNAME = Splache
LINKS = -lpthread
OBJ = object/Splache.o \
	object/Socket.o \
	object/HttpResponse.o

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

object/Splache.o : src/Splache.h src/Splache.cpp src/Socket.h src/Splache.h
	$(CXX) -c src/Splache.cpp -o object/Splache.o

object/Socket.o : src/Socket.h src/Socket.cpp
	$(CXX) -c src/Socket.cpp -o object/Socket.o

object/HttpResponse.o : src/HttpResponse.h src/HttpResponse.cpp
	$(CXX) -c src/HttpResponse.cpp -o object/HttpResponse.o

