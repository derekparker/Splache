#ifndef H_FILEHANDLER
#define H_FILEHANDLER

#include <stdio.h>
#include <stdlib.h>

class FileHandler{

 public:
  //holds the size of the file.
  int size;
  
  char* getFile(const char*);
  //I don't want to deal with this one yet.
  //static const bool putFile(char*, char*);
};
#endif
