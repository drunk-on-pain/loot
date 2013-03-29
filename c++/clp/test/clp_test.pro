#-------------------------------------------------
#
# Project created by QtCreator 2012-03-01T20:08:16
#
#-------------------------------------------------
TARGET = clp_test

TEMPLATE = app
CONFIG   += console c++11
CONFIG   -= app_bundle
QT -= gui

INCLUDEPATH += ..

SOURCES += test.cpp \
    main.cpp

DEFINES += "GTEST_HAS_TR1_TUPLE=0"

macx {
    QMAKE_CXXFLAGS += -mmacosx-version-min=10.7 -stdlib=libc++
}

LIBS += -L..
LIBS += -lloot_clp -lgtest -lc++
