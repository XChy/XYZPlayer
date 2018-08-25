#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractTableModel>
#include <XYZPlayer/MusicPlayer.h>

class PlaylistModel : public QAbstractTableModel
{
public:
	PlaylistModel(QObject* parent=nullptr);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	MusicPlayer* player() const;
	void setPlayer(MusicPlayer* player);

	bool setData(const QModelIndex& index, const QVariant& v, int role = Qt::EditRole);
public slots:
	void refresh();
private:
	MusicPlayer* mPlayer;
};

#endif // PLAYLISTMODEL_H
