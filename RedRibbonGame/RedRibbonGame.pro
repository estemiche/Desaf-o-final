QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    muros.cpp \
    nivel.cpp \
    obstaculos.cpp \
    personajes.cpp

HEADERS += \
    mainwindow.h \
    muros.h \
    nivel.h \
    obstaculos.h \
    personajes.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Sprite.qrc

DISTFILES += \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/Muros2.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/Nivel.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/Nivel1.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/Nivel2.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/Obstaculos.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/Personajes.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/Personajes2.txt
