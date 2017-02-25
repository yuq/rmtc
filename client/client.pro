QT += qml quick

TARGET   = rmtc

SOURCES += main.cpp \
    rmtc_services.cpp
HEADERS += \
    rmtc_services.h
OTHER_FILES += main.qml

CONFIG += link_pkgconfig
PKGCONFIG += libqtrpc2
