


#----------------------------Specific Includes for linux---------------------------------

linux {
    # include paths
    #INCLUDEPATH += $$PWD/../lib/armadillo-3.910.0/include

    # header files
   # HEADERS  += $$PWD/../lib/armadillo-3.910.0/include/armadillo

    #LIBS += -L/usr/lib -lblas
    #LIBS += -L/usr/lib -llapack
    LIBS += -L/usr/lib -larmadillo
}

#----------------------------Specific Includes for mac os---------------------------------

#/Library/Frameworks
#mac: LIBS +=  -framework Accelerate
#mac: LIBS += -llapack -lblas

#----------------------------Specific Includes for windows---------------------------------

win32 {
    # include paths
    INCLUDEPATH += $$PWD/../lib/armadillo-3.910.0/include

    # header files
    HEADERS  += $$PWD/../lib/armadillo-3.910.0/include/armadillo
    !contains(QMAKE_HOST.arch, x86_64) {

        message("x86 build")

        ## Windows x86 (32bit) specific build here

LIBS += -L$$PWD/../lib/armadillo-3.910.0/examples/lib_win32/ -lblas_win32_MT

INCLUDEPATH += $$PWD/../lib/armadillo-3.910.0/examples/lib_win32
DEPENDPATH += $$PWD/../lib/armadillo-3.910.0/examples/lib_win32

LIBS += -L$$PWD/../lib/armadillo-3.910.0/examples/lib_win32/ -llapack_win32_MT

INCLUDEPATH += $$PWD/../lib/armadillo-3.910.0/examples/lib_win32
DEPENDPATH += $$PWD/../lib/armadillo-3.910.0/examples/lib_win32

    } else {

        ## Windows x64 (64bit) specific build here

        message("x86_64 build")

LIBS += -L$$PWD/../lib/armadillo-3.910.0/examples/lib_win64/ -lblas_win64_MT

INCLUDEPATH += $$PWD/../lib/armadillo-3.910.0/examples/lib_win64
DEPENDPATH += $$PWD/../lib/armadillo-3.910.0/examples/lib_win64

LIBS += -L$$PWD/../lib/armadillo-3.910.0/examples/lib_win64/ -llapack_win64_MT

INCLUDEPATH += $$PWD/../lib/armadillo-3.910.0/examples/lib_win64
DEPENDPATH += $$PWD/../lib/armadillo-3.910.0/examples/lib_win64

    }

}
