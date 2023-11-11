TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \

HEADERS += \
    log_duration.h \
    shapes.h

DISTFILES += \
    libshape_dll.dll
