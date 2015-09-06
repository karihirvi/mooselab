#ifndef %ClassName:u%_H
#define %ClassName:u%_H

#include <memory>
#include <QObject>
#include "cpp14.h"

namespace mooselab 
{
class %ClassName% : public QObject {
  Q_OBJECT
public:
  explicit %ClassName%(QObject *parent = 0);
  // If you want to create a value type, remove the QObject inheritance
  // and the delete's and uncomment the corresponding implementations
  // in the *.cpp file.
  %ClassName%(%ClassName%&& rhs) = delete;
  %ClassName%& operator=(%ClassName%&& rhs) = delete;
  %ClassName%(const %ClassName%& rhs) = delete;
  %ClassName%& operator=(const %ClassName%& rhs) = delete;
  ~%ClassName%();
  
private:
  struct D;
  std::unique_ptr<D> d_;
};
  
}
#endif // zenniz::%ClassName:u%_H

