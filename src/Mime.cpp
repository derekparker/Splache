#include "Mime.h"

MIME::MIME()
{
  MIMETYPES["jpg"] = "image/jpeg;";
  MIMETYPES["jpeg"] = "image/jpeg;";
  MIMETYPES["gif"] = "image/gif;";
  MIMETYPES["png"] = "image/png;";
  MIMETYPES["tiff"] = "image/tiff;";

  MIMETYPES["css"] = "text/css;";
  MIMETYPES["csv"] = "text/csv;";
  MIMETYPES["js"] = "text/javascript;";
  MIMETYPES["txt"] = "text/plain;";
  MIMETYPES["xml"] = "text/xml;";
  MIMETYPES["html"] = "text/html;";

  MIMETYPES["pdf"] = "application/pdf;";
  /*More to come. These will suffice for now.*/
}

const char* MIME::getMimeType(const char* fileExtension)
{
  return MIMETYPES[fileExtension].c_str();
}
