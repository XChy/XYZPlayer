#ifndef BIOWIDGET_H
#define BIOWIDGET_H

#include <QLabel>
#include <XYZPlayer/MusicPlayer.h>

class BioWidget : public QWidget
{
	Q_OBJECT
public:
	explicit BioWidget(QWidget *parent = nullptr);

	void resizeEvent(QResizeEvent* e);

	MusicPlayer* player() const;
public slots:
	void setPlayer(MusicPlayer* player);
protected:
	void onLoadedPicture(int index);
	void onCurrentIndexChanged(int oldIndex,int newIndex);
private:
	MusicPlayer* mPlayer;
	QLabel* mPictureLabel;
	void updatePicture();
};

#endif // BIOWIDGET_H
