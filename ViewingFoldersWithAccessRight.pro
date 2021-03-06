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
    role_matrix_widget.cpp \
    file_system_view_widget.cpp \
    matrix_widget.cpp \
    access_right_matrix_widget.cpp \
    permission_filter_model.cpp \
    matrixes_widget.cpp \
    create_items_widget.cpp

HEADERS  += widget.h \
    application.h \
    system_access_right.h \
    file_system_permission_model.h \
    user.h \
    role.h \
    access_right.h \
    database.h \
    file_system_path_right.h \
    role_matrix_widget.h \
    file_system_view_widget.h \
    matrix_widget.h \
    access_right_matrix_widget.h \
    permission_filter_model.h \
    matrixes_widget.h \
    create_items_widget.h
