#ifndef CUSTOMWINDOWWRAPPER_H
#define CUSTOMWINDOWWRAPPER_H

#include <QWidget>
#include <QtEvents>
#include <QAbstractButton>
#include <QPainter>
#include <QtMath>
#include "MusicUtil.h"

class FramelessWindow : public QWidget
{
	Q_OBJECT
public:
    explicit FramelessWindow(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent* e);
    void changeEvent(QEvent* e);
    void paintEvent(QPaintEvent *e);

	QWidget* content() const;
	QWidget* titleBar() const;

signals:
	void windowStateChanged(Qt::WindowStates state);
public slots:
	void setContent(QWidget* content);
	void setTitleBar(QWidget* titleBar);
	void toggleMaximize();
    bool eventFilter(QObject* watched, QEvent* event);

private:
	QWidget* mContent;
	QWidget* mTitleBar;

	QPoint origin;
    bool isMoving;
};

#endif // CUSTOMWINDOWWRAPPER_H
