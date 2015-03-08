QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(qtxlsx/src/xlsx/qtxlsx.pri)

TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp \
    MainWindow.cpp \
    ParseExcel.cpp \
    Controller.cpp \
    WriteExcel.cpp

HEADERS += \
    Matching.h \
    MainWindow.h \
    ParseExcel.h \
    Controller.h \
    WriteExcel.h \
    global.h

OTHER_FILES += \
    out.txt

FORMS += \
    MainWindow.ui

