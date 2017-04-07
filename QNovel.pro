#-------------------------------------------------
#
# Project created by QtCreator 2017-04-06T11:48:59
#
#-------------------------------------------------

####http://stackoverflow.com/questions/15078060/embedding-python-in-qt-5####

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QNovel
TEMPLATE = app

CONFIG += c++11


#QMAKE_LFLAGS += -F/Library/Frameworks/

INCLUDEPATH += -I $$PWD/pybind11/include \
           -I /usr/local/Cellar/python3/3.5.2_3/Frameworks/Python.framework/Versions/3.5/include/python3.5m

QMAKE_CFLAGS += -Wno-unused-result -Wsign-compare -Wunreachable-code -fno-common -dynamic -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes

LIBS += -L/usr/local/Cellar/python3/3.5.2_3/Frameworks/Python.framework/Versions/3.5/lib/python3.5/config-3.5m -lpython3.5m -ldl -framework CoreFoundation


SOURCES += main.cpp\
        mainwindow.cpp \
        globalmanager.cpp \
        historydelegate.cpp

HEADERS  += mainwindow.h \
        globalmanager.h \
        historydelegate.h

FORMS    += mainwindow.ui

DISTFILES += \
    scripts/main.py \
    scripts/db.py
