#include "GeneralException.h"

void GeneralException::logExceptionToFile(Log& logger)
{
  logger.logException((char*)m_s.c_str());
}
