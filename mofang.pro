QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT       +=opengl
QT       += core gui openglwidgets
QT       += widgets
SOURCES += \
    cglobal.cpp \
    cubes.cpp \
    cubesstate.cpp \
    input_action.cpp \
    main.cpp \
    setwindow.cpp \
    show2d.cpp \
    solvefunction.cpp \
    transform3d.cpp \
    window.cpp

HEADERS += \
    cglobal.h \
    cubes.h \
    cubesstate.h \
    input_action.h \
    setwindow.h \
    show2d.h \
    solvefunction.h \
    transform3d.h \
    vertex.h \
    window.h

FORMS += \
    input_action.ui \
    setwindow.ui \
    show2d.ui \
    window.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
