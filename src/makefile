CXX = g++ -ggdb -std=c++11
BINNAME = Splache
OBJ = object/Splache.o
LINKS = -lpthread

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

object/Splache.o : Splache.h Splache.cpp
	$(CXX) -c Splache.cpp -o object/Splache.o

