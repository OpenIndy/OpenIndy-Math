


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

win32 {
    CONFIG(release, debug|release) {
        dlltarget.path = $$PWD/../install/release
    } else {
        dlltarget.path = $$PWD/../install/debug
    }
    INSTALLS += dlltarget
}

linux {
    CONFIG(release, debug|release) {
        librarytarget.path = $$PWD/../install/release
    } else {
        librarytarget.path = $$PWD/../install/debug
    }
    CONFIG(debug, debug|release):librarytarget.files = $$PWD/../bin/debug/*.so*
    CONFIG(release, debug|release):librarytarget.files = $$PWD/../bin/release/*.so*
    INSTALLS += librarytarget
}


# blas / lapack
win32 {

    win32:CONFIG(release, debug|release): blaslapack.path = $$PWD/../install/release
    win32:CONFIG(debug, debug|release): blaslapack.path = $$PWD/../install/debug

    !contains(QT_ARCH, x86_64) {
        blaslapack.files += $$PWD/../lib/armadillo-3.910.0/examples/lib_win32/blas_win32_MT.dll
        blaslapack.files += $$PWD/../lib/armadillo-3.910.0/examples/lib_win32/lapack_win32_MT.dll
    } else {
        blaslapack.files += $$PWD/../lib/armadillo-3.910.0/examples/lib_win64/blas_win64_MT.dll
        blaslapack.files += $$PWD/../lib/armadillo-3.910.0/examples/lib_win64/lapack_win64_MT.dll
    }

    INSTALLS += blaslapack

}
