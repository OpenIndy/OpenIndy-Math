


#----------------------------Specific Includes for linux---------------------------------

linux {
    # Switch via qmake: "USE_SYSTEM_ARMADILLO=true|false"
    # Default keeps existing behavior (system armadillo).
    isEmpty(USE_SYSTEM_ARMADILLO): USE_SYSTEM_ARMADILLO = true
    ARMADILLO_DIR = armadillo-3.910.0

    equals(USE_SYSTEM_ARMADILLO, true) {
        message("Linux: using system armadillo")
        LIBS += -L/usr/lib -larmadillo
    } else {
        message("Linux: using bundled armadillo (build + link)")
        ARMADILLO_BUNDLED_LIB = $$PWD/../lib/libarmadillo.so

        INCLUDEPATH += $$PWD/../lib/$$ARMADILLO_DIR/include
        HEADERS += $$PWD/../lib/$$ARMADILLO_DIR/include/armadillo

        # Build bundled armadillo wrapper library before linking this target.
        armadillo_bundled.target = $$ARMADILLO_BUNDLED_LIB
        armadillo_bundled.depends = $$PWD/../lib/armadillo.pro $$PWD/../lib/$$ARMADILLO_DIR/src/wrap_libs.cpp
        armadillo_bundled.commands = cd $$PWD/../lib && qmake armadillo.pro -spec linux-g++ && $(MAKE)
        QMAKE_EXTRA_TARGETS += armadillo_bundled
        PRE_TARGETDEPS += $$ARMADILLO_BUNDLED_LIB

        LIBS += -L$$PWD/../lib -larmadillo -lblas -llapack
    }
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

    win32:CONFIG(release, debug|release): blaslapack.path = $$PWD/../install/release
    win32:CONFIG(debug, debug|release): blaslapack.path = $$PWD/../install/debug

    !contains(QT_ARCH, x86_64) {
        blaslapack.files += $$PWD/../lib/armadillo-3.910.0/examples/lib_win32/blas_win32_MT.dll
        blaslapack.files += $$PWD/../lib/armadillo-3.910.0/examples/lib_win32/lapack_win32_MT.dll
    } else {
        blaslapack.files += $$PWD/../lib/armadillo-3.910.0/examples/lib_win64/blas_win64_MT.dll
        blaslapack.files += $$PWD/../lib/armadillo-3.910.0/examples/lib_win64/lapack_win64_MT.dll
    }

    blaslapack.CONFIG += no_check_exist
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
        librarytarget.extra = mkdir -p $$librarytarget.path && cp -a $$PWD/../bin/release/*.so* $$librarytarget.path/
    } else {
        librarytarget.path = $$PWD/../install/debug
        librarytarget.extra = mkdir -p $$librarytarget.path && cp -a $$PWD/../bin/debug/*.so* $$librarytarget.path/
    }
    librarytarget.CONFIG += no_check_exist
    INSTALLS += librarytarget

    equals(USE_SYSTEM_ARMADILLO, false) {
        CONFIG(release, debug|release) {
            armadillotarget.path = $$PWD/../install/release
        } else {
            armadillotarget.path = $$PWD/../install/debug
        }
        armadillotarget.files = $$PWD/../lib/libarmadillo.so
        armadillotarget.CONFIG += no_check_exist
        INSTALLS += armadillotarget
    }
}

