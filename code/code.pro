QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base_pecas.cpp \
    bispo_peca.cpp \
    cavalo_peca.cpp \
    dama_peca.cpp \
    funcoes_auxiliares.cpp \
    main.cpp \
    peao_peca.cpp \
    rei_peca.cpp \
    torre_peca.cpp

HEADERS += \
    base_pecas.h \
    bispo_peca.h \
    cavalo_peca.h \
    dama_peca.h \
    funcoes_auxiliares.h \
    peao_peca.h \
    rei_peca.h \
    torre_peca.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
