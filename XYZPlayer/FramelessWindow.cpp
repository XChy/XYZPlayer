#include "FramelessWindow.h"

static int contenMargin=5;

FramelessWindow::FramelessWindow(QWidget *parent)
	: QWidget(parent),
	  mContent(nullptr),
	  mTitleBar(nullptr),
	  isMoving(false)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	MusicUtil::loadMainWindowSetting(this);
}

void FramelessWindow::resizeEvent(QResizeEvent* e)
{
	if(mContent){
		switch (windowState()) {
		case Qt::WindowMaximized:
			mContent->setGeometry(rect());
			break;
		default:
			mContent->setGeometry(contenMargin,contenMargin,e->size().width()-contenMargin*2,e->size().height()-contenMargin*2);;
		}
	}
}

void FramelessWindow::paintEvent(QPaintEvent *e)
{
	QPainterPath path;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	QColor color(10, 10, 10, 40);
	for(int i=0; i<contenMargin; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRoundedRect(contenMargin-i, contenMargin-i, this->width()-(contenMargin-i)*2, this->height()-(contenMargin-i)*2,contenMargin/3,contenMargin/3);
		color.setAlpha(120 - qSqrt(i)*50);
		painter.setPen(color);
		painter.drawPath(path);
	}
}

void FramelessWindow::changeEvent(QEvent *e)
{
	if(e->type()==QEvent::WindowStateChange&&mContent){
		switch (windowState()) {
		case Qt::WindowMaximized:
			mContent->setGeometry(rect());
			break;
		default:
			mContent->setGeometry(contenMargin,contenMargin,width()-contenMargin*2,height()-contenMargin*2);;
		}
		emit windowStateChanged(windowState());
	}
}

void FramelessWindow::setContent(QWidget* content)
{
	if(mContent){
		mContent->setParent(nullptr);
	}
	if(content){
		content->setParent(this);
		content->setGeometry(contenMargin,contenMargin,width()-contenMargin*2,height()-contenMargin*2);
	}
	mContent=content;
}

void FramelessWindow::setTitleBar(QWidget* titleBar)
{
	if(mTitleBar){
		mTitleBar->removeEventFilter(this);
	}
	if(titleBar){
		titleBar->installEventFilter(this);
	}
	mTitleBar=titleBar;
}

void FramelessWindow::toggleMaximize()
{
	if(isMaximized()){
		showNormal();
	}else{
		showMaximized();
	}
}

bool FramelessWindow::eventFilter(QObject* watched, QEvent* event)
{
	if(watched==mTitleBar){
		if(event->type()==QEvent::MouseButtonPress){
			origin=static_cast<QMouseEvent*>(event)->pos();
			isMoving=true;
			return true;
		}else if(event->type()==QEvent::MouseMove){
			if(isMoving){
				if(isMaximized()){
					showNormal();
				}
				move(static_cast<QMouseEvent*>(event)->globalPos()-mTitleBar->mapTo(this,origin));
				return true;
			}
		}else if(event->type()==QEvent::MouseButtonRelease){
			isMoving=false;
			return true;
		}

	}
	return QWidget::eventFilter(watched,event);
}

QWidget* FramelessWindow::titleBar() const
{
	return mTitleBar;
}

FramelessWindow::~FramelessWindow()
{
	MusicUtil::saveMainWindowSetting(this);
}

QWidget* FramelessWindow::content() const
{
	return mContent;
}
