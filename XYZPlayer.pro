#-------------------------------------------------
#
# Project created by QtCreator 2018-08-13T20:18:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XYZPlayer
TEMPLATE = app

INCLUDEPATH+=D:\Library-Cpp\QtAV\include
LIBS+=-L D:\Library-Cpp\QtAV\lib\ -lavcodec -lavdevice -lavfilter -lavformat -lavresample  -lavutil -lQtAV1 -lswresample -lswscale

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
	XYZPlayer/main.cpp \
	XYZPlayer/MainWindow.cpp \
    XYZPlayer/MusicPlayer.cpp \
    XYZPlayer/MusicObject.cpp \
    XYZPlayer/PlaylistView.cpp \
    XYZPlayer/ItemDelegates.cpp

HEADERS += \
	XYZPlayer/MainWindow.h \
    XYZPlayer/MusicPlayer.h \
    XYZPlayer/MusicObject.h \
    XYZPlayer/PlaylistView.h \
    XYZPlayer/ItemDelegates.h

FORMS += \
	XYZPlayer/MainWindow.ui

RESOURCES += \
    res/res.qrc

RC_ICONS=res/images/logo.ico
