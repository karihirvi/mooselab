#ifndef EXCEPTION_GLOBAL_H
#define EXCEPTION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EXCEPTION_LIBRARY)
#  define EXCEPTIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define EXCEPTIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // EXCEPTION_GLOBAL_H
