#include "appassert.h"
#include "enumdemo.h"
#include <QHash>
#include "appenum.h"
#include "defs.h"

namespace
{
// mapped enums
QHash<qint32,
  AppEnum<mooselab::EnumDemo::MyEnum, SimpleContent>> simple_enum_hash;
//AppEnum<mooselab::EnumDemo::Select, SimpleContent> aa;

void FillHash()
{
  typedef mooselab::EnumDemo::MyEnum T;
  typedef SimpleContent S;
  QList<T> types = {T::kOne, T::kTwo, T::kThree};
  QList<S> contents = {S("one"), S("two"), S("three")};
  Fill<T>(types, contents, &simple_enum_hash);
}

int init()
{
  FillHash();
  return 0;
}

// just to execute the function during module load
UNUSED_VAR int dummy = init();
}

namespace mooselab
{

struct EnumDemo::D
{
  D(EnumDemo *host) : host_(host) {}

  EnumDemo *host_;

};

//*************************************************************************
//*************************************************************************
//*************************************************************************

EnumDemo::EnumDemo(QObject *parent) : QObject(parent),
  d_(std::make_unique<D>(this))
{
}

QVector<EnumDemo::MyEnum> EnumDemo::enum_values() const
{
  return ::CreateEnumList<EnumDemo::MyEnum>(::simple_enum_hash);
}

EnumDemo::MyEnum EnumDemo::int_to_enum(int value) const
{
  return ::TypeFromNumber<EnumDemo::MyEnum>(value, ::simple_enum_hash);
}

SimpleContent EnumDemo::content_for_enum(EnumDemo::MyEnum value) const
{
  return ::simple_enum_hash[static_cast<qint32>(value)].content;
}

EnumDemo::~EnumDemo() = default;


//EnumDemo::EnumDemo(EnumDemo &&rhs) : d_(std::move(rhs.d_))
//{
//  d_->host_ = this;
//}

//EnumDemo& EnumDemo::operator=(EnumDemo &&rhs)
//{
//  d_ = std::move(rhs.d_);
//  d_->host_ = this;
//  return *this;
//}

//EnumDemo::EnumDemo(const EnumDemo &rhs) :
//  d_(std::make_unique<D>(*rhs.d_))
//{
//  d_->host_ = this;
//}

//EnumDemo& EnumDemo::operator=(const EnumDemo &rhs)
//{
//  *d_ = *rhs.d_;
//  d_->host_ = this;
//  return *this;
//}

}
