include($${top_srcdir}/utilities.pri)

QT       += core

QT       -= gui

TARGET = run
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# include exception
INCLUDEPATH += $${top_srcdir}/exception
LIBS += -L$${DESTDIR} -lexception$${D}

SOURCES += main.cpp \
    demo.cpp \
    client.cpp

HEADERS += \
    demo.h \
    client.h
