#-------------------------------------------------
#
# Project created by QtCreator 2018-04-02T20:06:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViewingFoldersWithAccessRight
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    application.cpp \
    system_access_right.cpp \
    file_system_permission_model.cpp \
    user.cpp \
    role.cpp \
    access_right.cpp \
    database.cpp \
    file_system_path_right.cpp \
    role_matrix_widget.cpp

HEADERS  += widget.h \
    application.h \
    system_access_right.h \
    file_system_permission_model.h \
    user.h \
    role.h \
    access_right.h \
    database.h \
    file_system_path_right.h \
    role_matrix_widget.h
