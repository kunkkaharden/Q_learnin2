QT += core
QT -= gui

CONFIG += c++11

TARGET = Q_learnin2
CONFIG += console
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

LIBS += -lgomp
TEMPLATE = app

SOURCES += main.cpp \
    agente.cpp \
    cordenadas.cpp \
    entorno.cpp \
    estado.cpp \
    estado_recompensa.cpp \
    matrix.cpp \
    q_learning.cpp \
    qlearning.cpp \
    recompensa_estado.cpp \
    agenteP.cpp \
    qlearnigp.cpp \
    agentepa.cpp

HEADERS += \
    agente.h \
    cordenadas.h \
    entorno.h \
    estado.h \
    estado_recompensa.h \
    matrix.h \
    q_learning.h \
    qlearning.h \
    recompensa_estado.h \
    agenteP.h \
    qlearnigp.h \
    agentepa.h
