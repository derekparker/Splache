#ifndef HELPER_H
#define HELPER_H

#include <string.h>

namespace stringHelper{

    //Cuts up a string you pass it based on a search parameter.
    //Finds the first instance of the search string, writes a
    //null terminator to the character at that index, and returns
    //a pointer to the second character.
    char* cutString(char*, char*);
    
}

#endif
