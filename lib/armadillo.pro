TEMPLATE = lib
TARGET = armadillo

CONFIG += c++11 warn_off
CONFIG += shared
CONFIG -= qt app_bundle

ARMADILLO_DIR = armadillo-3.910.0

INCLUDEPATH += $$PWD/$$ARMADILLO_DIR/include
DEPENDPATH += $$PWD/$$ARMADILLO_DIR/include

SOURCES += $$PWD/$$ARMADILLO_DIR/src/wrap_libs.cpp

unix:LIBS += -lblas -llapack
