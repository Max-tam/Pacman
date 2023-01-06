TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Source/gridmanagement.cpp \
        Source/pacman.cpp \
        Source/params.cpp \
        main.cpp

include(MinGL2/mingl.pri)

HEADERS += \
    En-têtes/gridmanagement.h \
    En-têtes/pacman.h \
    En-têtes/params.h \
    En-têtes/type.h

DISTFILES += \
    autre fichier/config.yaml \
    autre fichier/config.yaml \
    autre fichier/config.yaml
