#-------------------------------------------------
#
# Project created by QtCreator 2019-06-15T11:10:55
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseDesign_1_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        login.cpp \
        signup.cpp \
        user_dialog.cpp \
        global.cpp \
        ordered.cpp \


HEADERS  += mainwindow.h \
        dboperation.h \
        login.h \
        signup.h \
        user_dialog.h \
        global.h \
        ordered.h \
    dboperation.h


FORMS    += mainwindow.ui \
            login.ui \
            signup.ui \
            user_dialog.ui \
            ordered.ui

RESOURCES += \
    img.qrc
