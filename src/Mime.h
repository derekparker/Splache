
#ifndef MIME_H
#define MIME_H

#include <map>
#include <string>

class MIME{

  std::map<std::string, std::string> MIMETYPES;
 public:
  MIME();
  const char* getMimeType(const char* fileExtension);

};


#endif
