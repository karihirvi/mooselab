#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <QObject>
#include "cpp14.h"
#include "demo.h"


namespace mooselab
{
class Client : public QObject {
  Q_OBJECT
public:
  explicit Client(QObject *parent = 0);
  // If you want to create a value type, remove the QObject inheritance
  // and the delete's and uncomment the corresponding implementations
  // in the *.cpp file.
  Client(Client&& rhs) = delete;
  Client& operator=(Client&& rhs) = delete;
  Client(const Client& rhs) = delete;
  Client& operator=(const Client& rhs) = delete;
  ~Client();

  void set_demo(Demo *demo);

  void SwitchAssertDemo();
  void PreconditionAssertDemo();

private:
  struct D;
  std::unique_ptr<D> d_;
};

}
#endif // zenniz::CLIENT_H


