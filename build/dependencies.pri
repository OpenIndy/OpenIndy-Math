


#----------------------------Specific Includes for linux---------------------------------

linux {
    LIBS += -L/usr/lib -larmadillo
}

#----------------------------Specific Includes for mac os---------------------------------

#/Library/Frameworks
#mac: LIBS +=  -framework Accelerate
#mac: LIBS += -llapack -lblas

#----------------------------Specific Includes for windows---------------------------------

win32 {
    ARMADILLO=armadillo-3.910.0

    # include paths
    INCLUDEPATH += $$PWD/../lib/$$ARMADILLO/include

    # link
    LIBS += -L$$PWD/../lib/$$ARMADILLO/examples/lib_win64/ -lblas_win64_MT
    LIBS += -L$$PWD/../lib/$$ARMADILLO/examples/lib_win64/ -llapack_win64_MT

    # install
    CONFIG(release, debug|release): blaslapack.path = $$PWD/../install/release
    CONFIG(debug, debug|release): blaslapack.path = $$PWD/../install/debug

    blaslapack.files += $$PWD/../lib/$$ARMADILLO/examples/lib_win64/blas_win64_MT.dll
    blaslapack.files += $$PWD/../lib/$$ARMADILLO/examples/lib_win64/lapack_win64_MT.dll

    INSTALLS += blaslapack

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

