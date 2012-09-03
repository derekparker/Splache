/**
 *  SocketException.h
 *  
 *
 *  Created by Derek Parker and Kyle Nusbaum.
 */

#ifndef _SocketException_class
#define _SocketException_class

#include "GeneralException.h"

class SocketException : public GeneralException
{
 public:
 
 SocketException(std::string s) : GeneralException(s){
        //printf("%s\n",s.c_str());
        //printf("%s\n",m_s.c_str());
  };
  //using GeneralException::GeneralException(std::string);
  ~SocketException(){};
};


#endif
