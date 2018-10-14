#include "LyricsWidget.h"

LyricsWidget::LyricsWidget(QWidget *parent)
	: QWidget(parent),
      mLabelWhenNoLyrics(new QLabel(tr(
                                        "No lyrics found\nYou can <a>choose lyrics file</a>"
                                        ),this)),
	  mModel(new LyricsModel(this)),
	  mView(new LyricsView(this)),
	  mPlayer(nullptr)
{
    mLabelWhenNoLyrics->move(0,0);
    mLabelWhenNoLyrics->setWordWrap(true);
	mView->move(0,0);
	mView->setResizeMode(QListView::Adjust);
	mView->setItemDelegate(new LyricItemDelegate(this));
    mLabelWhenNoLyrics->raise();
    mLabelWhenNoLyrics->hide();
}

void LyricsWidget::resizeEvent(QResizeEvent* e)
{
    mLabelWhenNoLyrics->setFixedSize(size());
	mView->setFixedSize(size());
}

MusicPlayer* LyricsWidget::player() const
{
	return mPlayer;
}

void LyricsWidget::setPlayer(MusicPlayer* player)
{
	mModel->setPlayer(player);
	mView->setModel(mModel);
	mPlayer = player;
}
