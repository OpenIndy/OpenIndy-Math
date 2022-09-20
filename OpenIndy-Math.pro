CONFIG += c++11

TEMPLATE = subdirs

SUBDIRS = \
    math

# project locations
math.subdir = $$PWD/build

QMAKE_EXTRA_TARGETS += run-test
run-test.commands = rem