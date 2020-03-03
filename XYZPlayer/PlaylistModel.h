#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractTableModel>
#include <QMimeData>
#include <XYZPlayer/MusicPlayer.h>

class PlaylistModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	PlaylistModel(QObject* parent=nullptr);

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	virtual Qt::DropActions supportedDropActions() const;
	virtual Qt::DropActions supportedDragActions() const;

	virtual Qt::ItemFlags flags(const QModelIndex &index) const;

	virtual QStringList mimeTypes() const;

	virtual QMimeData* mimeData(const QModelIndexList &indexes) const;

	virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
								 int row, int column, const QModelIndex &parent) const;
	virtual bool dropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent);

	MusicPlayer* player() const;
	void setPlayer(MusicPlayer* player);

	virtual bool setData(const QModelIndex& index, const QVariant& v, int role = Qt::EditRole);
public slots:
	void onCurrentIndexChanged(int oldIndex,int newIndex);
	void onInfoLoaded(int index);
	void refresh();
private:
	MusicPlayer* _player;
};

#endif // PLAYLISTMODEL_H
