#include "appassert.h"
#include "client.h"

namespace mooselab
{

struct Client::D
{
  D(Client *host) : host_(host) {}

  Client *host_;
  Demo *demo_;

  void PreconditionAssertDemo()
  {
    // define a variable, but we don't know it's value yet
    Demo::MyEnum my_enum = Demo::MyEnum::kUndefined;
    // oops, forgot to set a valid value to the variable
    demo_->PreconditionAssert(my_enum);
  }

  void SwitchAssertDemo()
  {
    // oops, added an enum but forgot to add it to all switch statements
    demo_->SwitchAssert(Demo::MyEnum::kNewValue);
  }

};

Client::Client(QObject *parent) : QObject(parent),
  d_(std::make_unique<D>(this))
{
}

void Client::set_demo(Demo *demo)
{
  d_->demo_ = demo;
}

void Client::SwitchAssertDemo()
{
  d_->SwitchAssertDemo();
}

void Client::PreconditionAssertDemo()
{
  d_->PreconditionAssertDemo();
}

Client::~Client() = default;

//Client::Client(Client &&rhs) : d_(std::move(rhs.d_))
//{
//  d_->host_ = this;
//}

//Client& Client::operator=(Client &&rhs)
//{
//  d_ = std::move(rhs.d_);
//  d_->host_ = this;
//  return *this;
//}

//Client::Client(const Client &rhs) :
//  d_(std::make_unique<D>(*rhs.d_))
//{
//  d_->host_ = this;
//}

//Client& Client::operator=(const Client &rhs)
//{
//  *d_ = *rhs.d_;
//  d_->host_ = this;
//  return *this;
//}

}

