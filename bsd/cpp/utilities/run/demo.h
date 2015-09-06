#ifndef DEMO_H
#define DEMO_H

#include <memory>
#include <QObject>
#include "cpp14.h"

namespace mooselab
{
class Demo : public QObject {
  Q_OBJECT
public:
  explicit Demo(QObject *parent = 0);
  // If you want to create a value type, remove the QObject inheritance
  // and the delete's and uncomment the corresponding implementations
  // in the *.cpp file.
  Demo(Demo&& rhs) = delete;
  Demo& operator=(Demo&& rhs) = delete;
  Demo(const Demo& rhs) = delete;
  Demo& operator=(const Demo& rhs) = delete;
  ~Demo();

  enum class MyEnum:qint32 {
    kUndefined = -1, /**< Default value. This should never occur in running
      code */
    kYes = 0, /**< Valid value */
    kNo = 1, /**< Valid value */
    kNewValue = 2 /**< New enum added during development */
  };

  void SwitchAssert(MyEnum value);
  void PreconditionAssert(MyEnum value);

private:
  struct D;
  std::unique_ptr<D> d_;
};

}
#endif // zenniz::DEMO_H


