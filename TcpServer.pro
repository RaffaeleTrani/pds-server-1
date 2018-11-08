QT += core
QT += network
QT -= gui
QT += sql

TARGET = TcpServer
CONFIG   += console
CONFIG   -= app_bundle


TEMPLATE = app


SOURCES += main.cpp \
    mytcpserver.cpp

HEADERS += \
    mytcpserver.h
