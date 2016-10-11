#ifndef ENUMDEMO_H
#define ENUMDEMO_H

#include <memory>
#include <QObject>
#include "cpp14.h"
#include <QVector>
#include "appenum.h"
#include <functional>

namespace mooselab
{
class EnumDemo : public QObject {
  Q_OBJECT
public:
  explicit EnumDemo(QObject *parent = 0);
  EnumDemo(EnumDemo&& rhs) = delete;
  EnumDemo& operator=(EnumDemo&& rhs) = delete;
  EnumDemo(const EnumDemo& rhs) = delete;
  EnumDemo& operator=(const EnumDemo& rhs) = delete;
  ~EnumDemo();

  enum class MyEnum:int {
    kUndefined = -1,
    kOne = 1,
    kTwo = 2,
    kThree = 3
  };

  QVector<MyEnum> enum_values() const;
  MyEnum int_to_enum(int value) const;
  SimpleContent content_for_enum(MyEnum value) const;


private:

  struct D;
  std::unique_ptr<D> d_;
};

}
#endif // ENUMDEMO_H

