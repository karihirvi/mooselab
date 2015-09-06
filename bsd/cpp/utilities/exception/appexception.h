#ifndef APPEXCEPTION_H
#define APPEXCEPTION_H

#include <memory>
#include <exception>
#include <QObject>
#include "cpp14.h"
#include "exception_global.h"

#ifdef _NOEXCEPT
#define noexcept _NOEXCEPT
#endif

namespace mooselab
{
class EXCEPTIONSHARED_EXPORT AppException : public std::exception {
public:
  explicit AppException(const char *message = nullptr);
  AppException(AppException&& rhs);
  AppException& operator=(AppException&& rhs);
  AppException(const AppException& rhs);
  AppException& operator=(const AppException& rhs);
  ~AppException();

  virtual const char *what() const noexcept override;

private:
  struct D;
  std::unique_ptr<D> d_;
};

}
#endif // zenniz::APPEXCEPTION_H


