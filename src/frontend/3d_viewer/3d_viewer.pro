QT       += core gui opengl openglwidgets

include(3rdparty/QtGifImage-master/src/gifimage/qtgifimage.pri)
# include(3rdparty/QtGifImage-master/src/3dpartygifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    glview.cpp \
    mainwindow.cpp

HEADERS += \
    glview.h \
    mainwindow.h \
    ../../3d_viewer.h \
    3rdparty/QtGifImage-master/src/gifimage/qgifimage.h

FORMS += \
    glview.ui \
    mainwindow.ui

LIBS += \
    ../../lib3d_viewer.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
