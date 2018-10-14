#include <QApplication>
#include <QTranslator>
#include "MainContent.h"
#include "FramelessWindow.h"

//#ifdef Q_OS_WIN

//#include <windows.h>
//LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException){
//	QSettings settings;
//	settings.sync();
//	return EXCEPTION_EXECUTE_HANDLER;
//}

//#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationName("XYZPlayer");
	a.setOrganizationName("XYZPlayer");
//#ifdef Q_OS_WIN
//	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
//#endif
	QTranslator translator;
	translator.load("../languages/zh_CN");
	a.installTranslator(&translator);
	a.setStyleSheet(QStringLiteral("QMenu{"
								   "background-color:white;"
                                   "border: 1px solid #b2b2b2;"
								   "}"
								   "QMenuBar{"
								   "background-color:white;"
								   "border: 1px solid #b2b2b2;"
								   "}"
								   "#prevButton{"
								   "border-image:url(:/images/easy/previous.png);"
								   "}"
								   "#playButton[is_playing=true]{"
								   "border-image:url(:/images/easy/pause.png);"
								   "}"
								   "#playButton[is_playing=false]{"
								   "border-image:url(:/images/easy/play.png);"
								   "}"
								   "#nextButton{"
								   "border-image:url(:/images/easy/next.png);"
								   "}"
								   "#volumeButton[is_mute=true]{"
								   "border-image:url(:/images/easy/mute.png);"
								   "}"
								   "#volumeButton[is_mute=false]{"
								   "border-image:url(:/images/easy/volume.png);"
								   "}"
								   "#playbackModeButton[playbackmode=\"loop\"]{"
								   "border-image:url(:/images/easy/loop.png);"
								   "}"
								   "#playbackModeButton[playbackmode=\"current_loop\"]{"
								   "border-image:url(:/images/easy/current_loop.png);"
								   "}"
								   "#playbackModeButton[playbackmode=\"sequential\"]{"
								   "border-image:url(:/images/easy/sequential.png);"
								   "}"
								   "#playbackModeButton[playbackmode=\"random\"]{"
								   "border-image:url(:/images/easy/random.png);"
								   "}"
								   "QToolButton::menu-indicator{"
								   "image: none;"
								   "}"
								   "#titleBar{"
                                   "border-bottom: 1px solid #b2b2b2;"
								   "}"
								   "#footerWidget{"
                                   "border-top: 1px solid #b2b2b2;"
								   "}"
								   "#artistLabel{"
								   "font-size:14px;"
								   "font-family:宋体;"
								   "color:#666666;"
								   "}"
								   "#titleLabel{"
								   "font-size:13px;"
								   "font-family:宋体;"
								   "color:black;"
								   "}"
								   "#PictureLabel{"
								   "font-size:14px;"
								   "font-family:宋体;"
								   "}"
								   "#musicsLabel,#bioLabel,#lyricsLabel{"
								   "font-size:20px;"
								   "font-family:微软雅黑;"
								   "color:#b2b2b2;"
								   "}"
								   "#AddButton{"
								   "border-image:url(:/images/easy/add.png);"
								   "}"
                                   "#ClearButton{"
                                   "border-image:url(:/images/easy/clear.png);"
                                   "}"
								   "#settingButton{"
                                   "border-image:url(:/images/easy/settings.png);"
								   "}"
								   "#closeButton{"
								   "border-image:url(:/images/easy/close.png);"
                                   "}"
								   "#minButton{"
                                   "border-image:url(:/images/easy/minimize.png);"
								   "}"
                                   "#maxButton[isMaximized=false]{"
                                   "border-image:url(:/images/easy/maximize.png);"
								   "}"
                                   "#maxButton[isMaximized=false]{"
                                   "border-image:url(:/images/easy/maximize.png);"
                                   "}"
                                   "#maxButton[isMaximized=true]{"
                                   "border-image:url(:/images/easy/normalize.png);"
                                   "}"
								   "#musicsLabel[is_current=true],#bioLabel[is_current=true],#lyricsLabel[is_current=true]{"
								   "color:#00a1ec;"
								   "}"
								   "#PlaylistTitle{"
								   "font-size:15px;"
								   "font-family:微软雅黑;"
								   "color:black;"
								   "background-color:rgb(244,244,244);"
								   "}"
								   "QMenu::item{"
								   "color:black;"
								   "border:1px soild #b2b2b2;"
								   "background-color:white;"
								   "padding:2px 16px;"
								   "margin:2px 2px;"
								   "}"
								   "QMenu::item::selected{"
								   "background-color:#00a1ec;"
								   "}"
								   "QMainWindow{"
                                   "background-color:white;"
								   "}"
								   "#PlaylistView,#LocalMusicView{"
								   "color: black;"
								   "qproperty-showGrid:false;"
								   "qproperty-alternatingRowColors:true;"
								   "background-color:white;"
								   "alternate-background-color:#eeeeee;"
								   "selection-color:black;"
								   "selection-background-color:#cccccc;"
								   "border-radius: 0px;"
								   "padding: 2px 4px;"
								   "}"
								   "QTabWidget:tab-bar{"
								   "border-color:white;"
								   "}"
								   "QSlider::add-page:horizontal"
								   "{"
								   "background-color:#b2b2b2;"
								   "}"
								   "QSlider::sub-page:horizontal"
								   "{"
								   "background-color:#00a1ec;"
								   "}"
								   "QSlider::add-page:vertical"
								   "{"
								   "background-color:#00a1ec;"
								   "}"
								   "QSlider::sub-page:vertical"
								   "{"
								   "background-color:#b2b2b2;"
								   "}"
								   "QSlider::groove:horizontal"
								   "{"
								   "background:transparent;"
								   "height:6px;"
								   "}"
								   "QSlider::handle:horizontal"
								   "{"
								   "height:20px;"
								   "width:10px;"
								   "background:white;"
								   "border: 1px solid #b2b2b2;"
								   "margin: -8 0px;"
								   "}"
								   "QSlider::groove:vertical"
								   "{"
								   "background:transparent;"
								   "width:6px;"
								   "}"
								   "QSlider::handle:vertical"
								   "{"
								   "height:10px;"
								   "width:20px;"
								   "background:white;"
								   "border: 1px solid #b2b2b2;"
								   "margin: 0 -8px;"
								   "}"
								   "PlaylistView{"
								   "color: black;"
								   "qproperty-showGrid:false;"
								   "qproperty-alternatingRowColors:true;"
								   "background-color:white;"
								   "alternate-background-color:#eeeeee;"
								   "selection-color:black;"
                                   "selection-background-color:#dddddd;"
								   "border-radius: 0px;"
								   "padding: 2px 4px;"
								   "}"
								   "LyricsView{"
                                   "selection-background-color:#dddddd;"
								   "border: none;"
                                   "}"
								   ));
    FramelessWindow* wrapper=new FramelessWindow;
	wrapper->resize(900,700);
	MusicUtil::loadMainWindowSetting(wrapper);
	MainContent* w=new MainContent;

	QObject::connect(w,&MainContent::minimizeRequested,wrapper,&FramelessWindow::showMinimized);
	QObject::connect(w,&MainContent::toggleMaximizeRequested,wrapper,&FramelessWindow::toggleMaximize);
	QObject::connect(w,&MainContent::closeRequested,wrapper,&FramelessWindow::close);
	QObject::connect(wrapper,&FramelessWindow::windowStateChanged,w,&MainContent::updateMaximumButton);

	w->updateMaximumButton(wrapper->windowState());

	wrapper->setContent(w);
    wrapper->setTitleBar(w->titleBar());

	wrapper->show();

    w->player()->asyncLoadAllInfo();
    int ret=a.exec();
    MusicUtil::saveMainWindowSetting(wrapper);
	delete wrapper;
	return ret;
}
