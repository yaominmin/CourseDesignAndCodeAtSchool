#-------------------------------------------------
#
# Project created by QtCreator 2019-06-15T21:18:03
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = library
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    abouttxt.cpp \
    accountinfo.cpp \
    addbook.cpp \
    addreader.cpp \
    book.cpp \
    bookoperation.cpp \
    borrowbook.cpp \
    dboperation.cpp \
    first.cpp \
    helptxt.cpp \
    librarian.cpp \
    main.cpp \
    mainwindow.cpp \
    managereaders.cpp \
    modifypassword.cpp \
    managebooks.cpp \
    regist.cpp \
    reader.cpp \
    returnbook.cpp \
    searchBook.cpp \
    searchbyauthor.cpp \
    searchbybookname.cpp \
    searchbyisbn.cpp \
    searchbypublisher.cpp \
    user.cpp

HEADERS += \
    abouttxt.h \
    accountinfo.h \
    addbook.h \
    addreader.h \
    book.h \
    bookoperation.h \
    borrowbook.h \
    dboperation.h \
    first.h \
    helptxt.h \
    librarian.h \
    mainwindow.h \
    managereaders.h \
    modifypassword.h \
    managebooks.h \
    regist.h \
    reader.h \
    returnbook.h \
    searchBook.h \
    searchbyauthor.h \
    searchbybookname.h \
    searchbyisbn.h \
    searchbypublisher.h \
    user.h



FORMS += \
        mainwindow.ui \
    regist.ui \
    addreader.ui \
    addbook.ui \
    borrowbook.ui \
    returnbook.ui \
    first.ui \
    accountinfo.ui \
    managereaders.ui \
    modifypassword.ui \
    managebooks.ui \
    helptxt.ui \
    abouttxt.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES +=
