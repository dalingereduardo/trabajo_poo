QT += core gui widgets

TEMPLATE = app
CONFIG += c++17

SOURCES += \
    administradordanio.cpp \
    elemento.cpp \
    humano.cpp \
    ia.cpp \
    ia_aleatoria.cpp \
    ia_estrategica.cpp \
    ia_super.cpp \
    interfaz.cpp \
    jugador.cpp \
    main.cpp \
    partida.cpp

HEADERS += \
    administradordanio.h \
    elemento.h \
    humano.h \
    ia.h \
    ia_aleatoria.h \
    ia_estrategica.h \
    ia_super.h \
    interfaz.h \
    jugador.h \
    partida.h

FORMS += \
    interfaz.ui