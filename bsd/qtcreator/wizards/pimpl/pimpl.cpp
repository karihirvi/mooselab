#include "appassert.h"
#include "%ClassName:l%.%CppHeaderSuffix%"

namespace mooselab
{

struct %ClassName%::D
{
  D(%ClassName% *host) : host_(host) {}

  %ClassName% *host_;
  
};

//*************************************************************************
//*************************************************************************
//*************************************************************************

%ClassName%::%ClassName%(QObject *parent) : QObject(parent), 
  d_(std::make_unique<D>(this))
{
}

%ClassName%::~%ClassName%() = default;

//%ClassName%::%ClassName%(%ClassName% &&rhs) : d_(std::move(rhs.d_))
//{
//  d_->host_ = this;
//}

//%ClassName%& %ClassName%::operator=(%ClassName% &&rhs)
//{
//  d_ = std::move(rhs.d_);
//  d_->host_ = this;
//  return *this;
//}

//%ClassName%::%ClassName%(const %ClassName% &rhs) : 
//  d_(std::make_unique<D>(*rhs.d_))
//{
//  d_->host_ = this;
//}

//%ClassName%& %ClassName%::operator=(const %ClassName% &rhs)
//{
//  *d_ = *rhs.d_;
//  d_->host_ = this;
//  return *this;
//}
  
}
