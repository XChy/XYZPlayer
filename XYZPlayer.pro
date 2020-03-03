#-------------------------------------------------
#
# Project created by QtCreator 2018-08-13T20:18:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XYZPlayer
TEMPLATE = app

QMAKE_TARGET_PRODUCT = XYZPlayer
QMAKE_TARGET_DESCRIPTION = XYZPlayer

#QtAV path
INCLUDEPATH+=D:\Yu\Library-Cpp\build-QtAV\include
LIBS+=-L D:\Yu\Library-Cpp\build-QtAV\lib\ -lavcodec -lavdevice -lavfilter -lavformat -lavresample  -lavutil -lQtAV1 -lswresample -lswscale

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
    XYZPlayer/LocalmusicWidget.cpp \
    XYZPlayer/MusicLoader.cpp \
    XYZPlayer/SettingsDialog.cpp \
	XYZPlayer/main.cpp \
    XYZPlayer/MusicPlayer.cpp \
    XYZPlayer/MusicObject.cpp \
    XYZPlayer/PlaylistView.cpp \
    XYZPlayer/ItemDelegates.cpp \
    XYZPlayer/PlaylistModel.cpp \
    XYZPlayer/PlaylistWidget.cpp \
    XYZPlayer/BioWidget.cpp \
    XYZPlayer/MusicUtil.cpp \
    XYZPlayer/LyricsWidget.cpp \
    XYZPlayer/LyricsModel.cpp \
    XYZPlayer/LyricsView.cpp \
    XYZPlayer/MainContent.cpp \
    XYZPlayer/FramelessWindow.cpp

HEADERS += \
    XYZPlayer/LocalmusicWidget.h \
    XYZPlayer/MusicLoader.h \
    XYZPlayer/MusicPlayer.h \
    XYZPlayer/MusicObject.h \
    XYZPlayer/PlaylistView.h \
    XYZPlayer/ItemDelegates.h \
    XYZPlayer/PlaylistModel.h \
    XYZPlayer/PlaylistWidget.h \
    XYZPlayer/BioWidget.h \
    XYZPlayer/MusicUtil.h \
    XYZPlayer/LyricsWidget.h \
    XYZPlayer/LyricsModel.h \
    XYZPlayer/LyricsView.h \
    XYZPlayer/MainContent.h \
    XYZPlayer/FramelessWindow.h \
    XYZPlayer/SettingsDialog.h

FORMS += \
	XYZPlayer/MainWindow.ui \
	XYZPlayer/settingsdialog.ui

RESOURCES += \
    res/res.qrc

ICON =res/images/logo.ico
RC_ICONS = res/images/logo.ico

TRANSLATIONS += languages/zh_CN.ts

DISTFILES +=
