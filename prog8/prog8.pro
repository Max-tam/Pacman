TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Source/pacman.cpp \
        main.cpp

include(MinGL2/mingl.pri)

HEADERS += \
    En-têtes/pacman.h
