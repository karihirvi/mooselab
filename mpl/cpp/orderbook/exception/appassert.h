#ifndef APPASSERT
#define APPASSERT

#include <iostream>
#include "bugfoundexception.h"

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)
#define _THIS_LINE_ __FILE__ ": " LINE_STRING  " (" VER ")"


namespace mooselab
{

inline void AssertBug(bool condition, const char *msg) {
  if (!condition) {
#ifdef QT_DEBUG
    std::cout << msg << std::endl;
#endif
    throw BugFoundException(msg);
  }
}

inline void AssertCantReach(const char *msg) {
#ifdef QT_DEBUG
    std::cout << msg << std::endl;
#endif
  throw BugFoundException(msg);
}

}

#endif // APPASSERT

