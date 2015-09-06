#ifndef BUGFOUNDEXCEPTION_H
#define BUGFOUNDEXCEPTION_H

#include <memory>
#include <QObject>
#include "cpp14.h"
#include "appexception.h"
#include "exception_global.h"

namespace mooselab
{
class EXCEPTIONSHARED_EXPORT BugFoundException : public AppException {

public:
  explicit BugFoundException(const char *message);
  BugFoundException(BugFoundException&& rhs);
  BugFoundException& operator=(BugFoundException&& rhs);
  BugFoundException(const BugFoundException& rhs);
  BugFoundException& operator=(const BugFoundException& rhs);
  ~BugFoundException();

private:
  struct D;
  std::unique_ptr<D> d_;
};

}
#endif // zenniz::BUGFOUNDEXCEPTION_H


