#-------------------------------------------------
#
# Project created by QtCreator 2013-09-18T14:25:09
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4):

TARGET = openIndyMath
TEMPLATE = lib

DEFINES += OI_MATH_LIB

# version number from git
include($$PWD/version.pri)

# general build configuration
include($$PWD/config.pri)

# external libraries
include($$PWD/dependencies.pri)

# include paths
INCLUDEPATH += $$PWD/..
INCLUDEPATH += $$PWD/../src
INCLUDEPATH += $$PWD/../include

# source files
SOURCES += $$PWD/../src/oivec.cpp \
    $$PWD/../src/oimat.cpp \
    $$PWD/../src/laarmadillo.cpp \
    $$PWD/../src/chooselalib.cpp

# header files
HEADERS  += $$PWD/../include/global.h \
    $$PWD/../include/oivec.h \
    $$PWD/../include/oimat.h \
    $$PWD/../include/linearalgebra.h \
    $$PWD/../include/chooselalib.h \
    $$PWD/../src/laarmadillo.h
