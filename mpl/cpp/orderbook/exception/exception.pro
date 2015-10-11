include($${top_srcdir}/orderbook.pri)

QT       -= gui

TARGET = exception$${D}
TEMPLATE = lib

DEFINES += EXCEPTION_LIBRARY

SOURCES += \
    appexception.cpp \
    bugfoundexception.cpp

HEADERS +=\
        exception_global.h \
        cpp14.h \
    appexception.h \
    appassert.h \
    bugfoundexception.h

