CONFIG += c++11
QMAKE_CXXFLAGS_GNUCXX1Z          = -std=gnu++11

TEMPLATE = subdirs

SUBDIRS = \
    math

# project locations
math.subdir = $$PWD/build

QMAKE_EXTRA_TARGETS += run-test
run-test.commands = rem