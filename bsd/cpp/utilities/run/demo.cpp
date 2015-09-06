#include "appassert.h"
#include "demo.h"

namespace mooselab
{

struct Demo::D
{
  D(Demo *host) : host_(host) {}

  Demo *host_;

  void SwitchAssert(Demo::MyEnum value)
  {
    switch (value) {
    case Demo::MyEnum::kYes:
      // do domething
      break;
    case Demo::MyEnum::kNo:
      // do domething
      break;
    default:
      AssertCantReach(_THIS_LINE_);
      break;
    }
  }

  void PreconditionAssert(Demo::MyEnum value)
  {
    // precondition
    AssertBug(value != Demo::MyEnum::kUndefined, _THIS_LINE_);
    // proceed..
  }

};

Demo::Demo(QObject *parent) : QObject(parent),
  d_(std::make_unique<D>(this))
{
}

void Demo::SwitchAssert(MyEnum value)
{
  d_->SwitchAssert(value);
}

void Demo::PreconditionAssert(MyEnum value)
{
  d_->PreconditionAssert(value);
}

Demo::~Demo() = default;

//Demo::Demo(Demo &&rhs) : d_(std::move(rhs.d_))
//{
//  d_->host_ = this;
//}

//Demo& Demo::operator=(Demo &&rhs)
//{
//  d_ = std::move(rhs.d_);
//  d_->host_ = this;
//  return *this;
//}

//Demo::Demo(const Demo &rhs) :
//  d_(std::make_unique<D>(*rhs.d_))
//{
//  d_->host_ = this;
//}

//Demo& Demo::operator=(const Demo &rhs)
//{
//  *d_ = *rhs.d_;
//  d_->host_ = this;
//  return *this;
//}

}

