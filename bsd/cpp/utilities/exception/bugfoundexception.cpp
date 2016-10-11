#include "appassert.h"
#include "bugfoundexception.h"

namespace mooselab
{

struct BugFoundException::D
{
  D(BugFoundException *host) : host_(host) {}

  BugFoundException *host_;

};

BugFoundException::BugFoundException(const char *message) :
  AppException(message),
  d_(std::make_unique<D>(this))
{
}

BugFoundException::~BugFoundException() = default;

BugFoundException::BugFoundException(BugFoundException &&rhs)
  : d_(std::move(rhs.d_))
{
  d_->host_ = this;
}

BugFoundException& BugFoundException::operator=(BugFoundException &&rhs)
{
  d_ = std::move(rhs.d_);
  d_->host_ = this;
  return *this;
}

BugFoundException::BugFoundException(const BugFoundException &rhs) :
  AppException(rhs), d_(std::make_unique<D>(*rhs.d_))
{
  d_->host_ = this;
}

BugFoundException& BugFoundException::operator=(const BugFoundException &rhs)
{
  *d_ = *rhs.d_;
  d_->host_ = this;
  return *this;
}

}

