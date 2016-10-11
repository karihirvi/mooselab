#ifndef APPENUM_H
#define APPENUM_H

#include <QString>
/* Example how to use the enum template object

  // define hash
  QHash<qint32, AppEnum<MyEnumClass, SimpleContent>> enum_hash;
  // fill it with enums, undefined value is added by default
  typedef MyClassEnum T;
  QList<AppEnum> types = {T::kOne, T::kTwo};
  typedef SimpleContent S;
  QList<S> contents = {S("one"), S("two")};
  Fill<T>(types, contents, &enum_hash);
  // convert int to enum
  TypeFromNumber<MyEnumClass>(value, ::type_hash);
  // convert enum to string
  enum_hash[static_cast<qint32>(my_enum_class_value)].name;
  // to get a vector of enums
  CreateEnumList<MyEnumClass>(enum_hash);


  If EnumObject is not sufficient, create your own enum object
  and use the other more general template functions.

  References:
  http://www.gotw.ca/publications/mill17.htm
  http://www.cplusplus.com/forum/general/117444/  
  http://stackoverflow.com/questions/6477365/c-templates-template-double-template
*/

#include "appassert.h"

// enum template
template<typename T, typename STRUCT>
struct AppEnum {
  AppEnum() : value(T::kUndefined), number(static_cast<int>(T::kUndefined)),
    content(STRUCT()) {}
  AppEnum(T value, STRUCT const &content) : value(value),
    number(static_cast<int>(value)), content(content) {}

  // "true" enum class
  T value;
  // enum as int
  int number;
  // custom content struct associated with the enum
  STRUCT content;
};

struct SimpleContent {
  SimpleContent() : name("undefined") {}
  SimpleContent(QString const &name) : name(name) {}
  QString name;
};

//**********************************************************************
// Fill
//**********************************************************************

// Forward declaration
template<typename T, typename STRUCT, template<typename,typename> class Enum>
struct FillImpl;

// Function template, don't touch this
template<typename T, typename STRUCT, template<typename,typename> class Enum>
void Fill(QList<T> const &types, QList<STRUCT> const &contents,
          QHash<qint32, Enum<T, STRUCT>> *hash)
{
  FillImpl<T, STRUCT, Enum>::f(types, contents, hash);
}

// Helper function template which does the actual work
// (not in the "Why Not Specialize Function Templates?" article)
template<typename T, typename STRUCT, template<typename,typename> class Enum>
void FillImplF(QList<T> const &types, QList<STRUCT> const &contents,
          QHash<qint32, Enum<T, STRUCT>> *hash)
{
  mooselab::AssertBug(types.size() == contents.size(), _THIS_LINE_);
  // All enums have an undefined, which if default constructed
  (*hash)[static_cast<qint32>(T::kUndefined)] = Enum<T, STRUCT>();
  // Add the rest
  for (int i = 0; i < types.size(); i++) {
    (*hash)[static_cast<qint32>(types[i])]
        = Enum<T, STRUCT>(types[i], contents[i]);
  }
}

// Class template to specialize
template<typename T, typename STRUCT, template<typename,typename> class Enum>
struct FillImpl
{
  static void f(QList<T> const &types, QList<STRUCT> const &contents,
                 QHash<qint32, Enum<T, STRUCT>> *hash) {
    FillImplF(types, contents, hash);
  }
};

// Class template specialized to SimpleContent
template<typename T>
struct FillImpl<T, SimpleContent, AppEnum>
{
  static void f(QList<T> const &types, QList<SimpleContent> const &contents,
                 QHash<qint32, AppEnum<T, SimpleContent>> *hash) {
    FillImplF(types, contents, hash);
  }
};

//**********************************************************************
// CreateEnumList
//**********************************************************************

// Forward declaration
template<typename T, typename STRUCT, template<typename,typename> class Enum>
struct CreateEnumListImpl;

// Function template, don't touch this
template<typename T, typename STRUCT, template<typename,typename> class Enum>
QVector<T> CreateEnumList(QHash<qint32, Enum<T, STRUCT>> const &hash)
{
  return CreateEnumListImpl<T, STRUCT, Enum>::f(hash);
}

// Helper
template<typename T, typename STRUCT, template<typename,typename> class Enum>
QVector<T> CreateEnumListImplF(QHash<qint32, Enum<T, STRUCT>> const &hash)
{
  QVector<T> vec(hash.size());
  int i = 0;
  for (auto const &e: hash.values()) {
    vec[i++] = e.value;
  }
  return vec;
}

// Class template to specialize
template<typename T, typename STRUCT, template<typename,typename> class Enum>
struct CreateEnumListImpl
{
  static QVector<T> f(QHash<qint32, Enum<T, STRUCT>> const &hash) {
    return CreateEnumListImplF(hash);
  }
};

// Class template specialized to SimpleContent
template<typename T>
struct CreateEnumListImpl<T, SimpleContent, AppEnum>
{
  static QVector<T> f(QHash<qint32, AppEnum<T, SimpleContent>> const &hash) {
    return CreateEnumListImplF(hash);
  }
};

//**********************************************************************
// TypeFromNumber
//**********************************************************************

template<typename T, typename STRUCT, template<typename,typename> class Enum>
struct TypeFromNumberImpl;

// Function template, don't touch this
template<typename T, typename STRUCT, template<typename,typename> class Enum>
T TypeFromNumber(qint32 number, QHash<qint32, Enum<T, STRUCT>> const &hash)
{
  return TypeFromNumberImpl<T, STRUCT, Enum>::f(number, hash);
}

// Helper
template<typename T, typename STRUCT, template<typename,typename> class Enum>
T TypeFromNumberImplF(qint32 number,
                             QHash<qint32, Enum<T, STRUCT>> const &hash)
{
  T ret = T::kUndefined;
  for (auto const &en: hash.values()) {
    if (en.number == number) {
      ret = en.value;
      break;
    }
  }
  return ret;
}

// Class template to specialize
template<typename T, typename STRUCT, template<typename,typename> class Enum>
struct TypeFromNumberImpl
{
  static T f(qint32 number, QHash<qint32, Enum<T, STRUCT>> const &hash) {
    return TypeFromNumberImplF<T, STRUCT, Enum>(number, hash);
  }
};

// Speciaze to SimpleContent
template<typename T>
struct TypeFromNumberImpl<T, SimpleContent, AppEnum> {
  static T f(qint32 number,
             QHash<qint32, AppEnum<T, SimpleContent>> const &hash) {
    return TypeFromNumberImplF<T, SimpleContent, AppEnum>(number, hash);
  }
};


#endif // APPENUM_H
