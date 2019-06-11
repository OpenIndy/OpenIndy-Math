
# include paths
INCLUDEPATH += $$PWD/include
win32:CONFIG(release, debug|release): INCLUDEPATH += -L$$PWD/bin/release
else:win32:CONFIG(debug, debug|release): INCLUDEPATH += -L$$PWD/bin/debug
else:linux: CONFIG(debug, debug|release): INCLUDEPATH += -L$$PWD/bin/debug
else:linux: CONFIG(release, debug|release): INCLUDEPATH += -L$$PWD/bin/release

# depend paths
win32:CONFIG(release, debug|release): DEPENDPATH += -L$$PWD/bin/release
else:win32:CONFIG(debug, debug|release): DEPENDPATH += -L$$PWD/bin/debug
else:linux: CONFIG(debug, debug|release): DEPENDPATH += -L$$PWD/bin/debug
else:linux: CONFIG(release, debug|release): DEPENDPATH += -L$$PWD/bin/release

# header files
HEADERS  += \
    $$PWD/include/chooselalib.h \
    $$PWD/include/global.h \
    $$PWD/include/linearalgebra.h \
    $$PWD/include/oimat.h \
    $$PWD/include/oivec.h

# libraries
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/bin/release/ -lopenIndyMath1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/bin/debug/ -lopenIndyMath1
else:linux:CONFIG(release, debug|release): LIBS += -L$$PWD/bin/release/ -lopenIndyMath
else:linux:CONFIG(debug, debug|release): LIBS += -L$$PWD/bin/debug/ -lopenIndyMath
