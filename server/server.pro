QT += core network
QT -= gui

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

CONFIG += console
CONFIG -= app_bundle

TARGET   = rmtcd
TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    gpio.cpp \
    rmtc_services.cpp

HEADERS += \
    gpio.h \
    rmtc_services.h

CONFIG += link_pkgconfig
PKGCONFIG += libqtrpc2

DEFINES += CONFIG_ASYNC_GPIO
