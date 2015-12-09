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

GIT_VERSION = $$system(git --git-dir $$PWD/../.git --work-tree $$PWD describe --always --tags) # get git version
GIT_VERSION = $$replace(GIT_VERSION, "-g"{1}\w*, ) # remove commit hash after tag name
GIT_VERSION = $$replace(GIT_VERSION, "-", ".") # remove remaining hyphen
GIT_VERSION = $$replace(GIT_VERSION, "\b[0-9a-f]{5,40}\b", ) # remove commit hash (only if no tag has been set yet)

isEmpty(GIT_VERSION){
    message("no version")
}else{
    message($$GIT_VERSION)
    VERSION = $$GIT_VERSION
}

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/bin/debug
} else {
    DESTDIR = $$PWD/bin/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/include

SOURCES += src/oivec.cpp \
    src/oimat.cpp \
    src/laarmadillo.cpp \
    src/chooselalib.cpp

HEADERS  += include/global.h \
    include/oivec.h \
    include/oimat.h \
    include/linearalgebra.h \
    include/chooselalib.h \
    src/laarmadillo.h \
    lib/armadillo-3.910.0/include/armadillo


#----------------------------Specific Includes for linux---------------------------------

linux {
    LIBS += -L/usr/local/lib -lblas
    LIBS += -L/usr/local/lib -llapack
}

#----------------------------Specific Includes for mac os---------------------------------

#/Library/Frameworks
mac: LIBS +=  -framework Accelerate
#mac: LIBS += -llapack -lblas

#----------------------------Specific Includes for windows---------------------------------

win32 {

    ## Windows common build here

    !contains(QMAKE_HOST.arch, x86_64) {
        message("x86 build")

        ## Windows x86 (32bit) specific build here

LIBS += -L$$PWD/lib/armadillo-3.910.0/examples/lib_win32/ -lblas_win32_MT

INCLUDEPATH += $$PWD/lib/armadillo-3.910.0/examples/lib_win32
DEPENDPATH += $$PWD/lib/armadillo-3.910.0/examples/lib_win32

LIBS += -L$$PWD/lib/armadillo-3.910.0/examples/lib_win32/ -llapack_win32_MT

INCLUDEPATH += $$PWD/lib/armadillo-3.910.0/examples/lib_win32
DEPENDPATH += $$PWD/lib/armadillo-3.910.0/examples/lib_win32

    } else {
        message("x86_64 build")

LIBS += -L$$PWD/lib/armadillo-3.910.0/examples/lib_win64/ -lblas_win64_MT

INCLUDEPATH += $$PWD/lib/armadillo-3.910.0/examples/lib_win64
DEPENDPATH += $$PWD/lib/armadillo-3.910.0/examples/lib_win64

LIBS += -L$$PWD/lib/armadillo-3.910.0/examples/lib_win64/ -llapack_win64_MT

INCLUDEPATH += $$PWD/lib/armadillo-3.910.0/examples/lib_win64
DEPENDPATH += $$PWD/lib/armadillo-3.910.0/examples/lib_win64

    }
}

INCLUDEPATH += $$PWD/lib/armadillo-3.910.0/include
