INCLUDEPATH += ../shared

# Git current sha1
VERGIT = $$system(git rev-parse HEAD)
VERSTR = '\\"$${VERGIT}\\"'
DEFINES += VER=\"$${VERSTR}\"

# Set output dir
DESTDIR = $${top_builddir}/out

# Add 'd' for debug libs on windows
D=
win32:CONFIG(debug, debug|release):D=d

# Visual Studio has std::make_unique already
win32: DEFINES += SKIP_CPP14

# Needed for math constants (win & linux)
DEFINES += _USE_MATH_DEFINES

win32 {
  # Visual Studio parallel compile and x64
  QMAKE_CXXFLAGS += /FS /MP
  QMAKE_LFLAGS   += /MACHINE:X64
}

unix {
  # Require explicit return type
  QMAKE_CXXFLAGS += -Werror=return-type
  # Add directory of the executable ($ORIGIN) to the ld search path,
  # see, e.g., http://linux.die.net/man/8/ld-linux
  QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN\''
  # Add <executable>/../lib to library search path
  QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/../lib\''
}

# Unix: don't hard code additional library search paths to *.so's
#QMAKE_RPATH=
#QMAKE_RPATHLINKDIR += $${DESTDIR} $$[QT_INSTALL_LIBS] $$[QT_HOST_PREFIX]
