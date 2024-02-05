# https://arma.sourceforge.net/faq.html#linking
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

linux {
    LIBS += -L/usr/lib -larmadillo
}
