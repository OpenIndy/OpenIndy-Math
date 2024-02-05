# https://arma.sourceforge.net/faq.html#linking
win32 {
    ARMADILLO=armadillo-12.6.7
    # include paths
    INCLUDEPATH += $$PWD/../lib/$$ARMADILLO/include

    # link
    LIBS += -L$$PWD/../lib/$$ARMADILLO/examples/lib_win64/ -llibopenblas

    # install
    CONFIG(release, debug|release): blaslapack.path = $$PWD/../install/release
    CONFIG(debug, debug|release): blaslapack.path = $$PWD/../install/debug

    blaslapack.files += $$PWD/../lib/$$ARMADILLO/examples/lib_win64/libopenblas.dll

    INSTALLS += blaslapack
}

linux {
    LIBS += -L/usr/lib -larmadillo
    # LIBS += -lopenblas
}
