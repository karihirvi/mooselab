#include "appexception.h"

namespace mooselab
{

struct AppException::D
{
  D(AppException *host) : host_(host) {}

  AppException *host_;
  QString message_;
  QByteArray msg_;
};

AppException::AppException(const char *message) :
  d_(std::make_unique<D>(this))
{
  if (message != nullptr) {
    d_->message_ = QString(message);
  }
  d_->msg_ = d_->message_.toUtf8().append('\0');
}

AppException::~AppException() = default;

AppException::AppException(AppException &&rhs) : d_(std::move(rhs.d_))
{
  d_->host_ = this;
}

AppException& AppException::operator=(AppException &&rhs)
{
  d_ = std::move(rhs.d_);
  d_->host_ = this;
  return *this;
}

AppException::AppException(const AppException &rhs) :
  d_(std::make_unique<D>(*rhs.d_))
{
  d_->host_ = this;
}

AppException& AppException::operator=(const AppException &rhs)
{
  *d_ = *rhs.d_;
  d_->host_ = this;
  return *this;
}

const char *AppException::what() const noexcept
{
  return d_->msg_.data();
}


}

