
include(armadillo.pri)

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

