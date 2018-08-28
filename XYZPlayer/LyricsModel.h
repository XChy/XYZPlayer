#ifndef LYRICSMODEL_H
#define LYRICSMODEL_H

#include <QAbstractListModel>
#include <XYZPlayer/MusicPlayer.h>

class LyricsModel : public QAbstractListModel
{
	Q_OBJECT
public:
	LyricsModel(QObject* parent=nullptr);

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	MusicPlayer* player() const;
	void setPlayer(MusicPlayer* player);

	virtual bool setData(const QModelIndex& index, const QVariant& v, int role = Qt::EditRole);
public slots:
	void onPositionChanged(int64_t pos);
	void refresh();
private:
	MusicPlayer* mPlayer;
	int mLyricIndex;
};

#endif // LYRICSMODEL_H
