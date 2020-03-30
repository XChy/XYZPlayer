#include <QApplication>
#include <QTranslator>
#include <QMutex>
#include "MainContent.h"
#include "FramelessWindow.h"

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	static QMutex mutex;
	mutex.lock();
	QString text;
	switch(type)
		{
	case QtDebugMsg:
		text = QString("Debug:");
		break;
		case QtWarningMsg:
		text = QString("Warning:");
		break;
		case QtCriticalMsg:
		text = QString("Critical:");
		break;
		case QtFatalMsg:
		text = QString("Fatal:");
		}
	QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString current_date = QString("(%1)").arg(current_date_time);
	QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);
	QFile file("log.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream text_stream(&file);
	text_stream << message << "\r\n";
	file.flush();
	file.close();
	mutex.unlock();
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationName("XYZPlayer");
	a.setOrganizationName("XYZPlayer");
	QTranslator translator;
	translator.load("../languages/zh_CN");
	a.installTranslator(&translator);

	QFile style("://qss/easy.qss");

	if(style.open(QFile::ReadOnly)){
		a.setStyleSheet(style.readAll());
	}

	qInstallMessageHandler(outputMessage);

	FramelessWindow wrapper;
	wrapper.resize(900,700);
	MainContent* w=new MainContent;

	QObject::connect(w,&MainContent::minimizeRequested,&wrapper,&FramelessWindow::showMinimized);
	QObject::connect(w,&MainContent::toggleMaximizeRequested,&wrapper,&FramelessWindow::toggleMaximize);
	QObject::connect(w,&MainContent::closeRequested,&wrapper,&FramelessWindow::close);
	QObject::connect(&wrapper,&FramelessWindow::windowStateChanged,w,&MainContent::updateMaximumButton);

	w->updateMaximumButton(wrapper.windowState());

	wrapper.setContent(w);
	wrapper.setTitleBar(w->titleBar());
	wrapper.show();
	return a.exec();
}
