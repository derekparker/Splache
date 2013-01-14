#include "Helper.h"

namespace stringHelper{
    char* cutString(char * inStr, char * cutBy)
    {
        char* placeholder = strstr(inStr, cutBy);
        if(placeholder != 0)
        {
            placeholder[0] = 0;
            placeholder++;
        }
        return placeholder;
    }
    
    std::string *hostTrim(const char* inStr)
    {
        std::string *s = new std::string(inStr);
        s->erase(s->find(":",0));
    }
}

