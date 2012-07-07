#ifndef H_HTTPEXCEPTION
#define H_HTTPEXCEPTION

#include "GeneralException.h"

class HttpException : public GeneralException
{
 public:
 
  HttpException(std::string s) : GeneralException(s){};
  //using GeneralException::GeneralException(std::string);
  ~HttpException(){};
};


#endif
