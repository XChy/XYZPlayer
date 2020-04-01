#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractTableModel>
#include <QMimeData>
#include <QDataStream>
#include <XYZPlayer/MusicPlayer.h>

class PlaylistModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	PlaylistModel(QObject* parent=nullptr);

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	virtual Qt::DropActions supportedDropActions() const override;
	virtual Qt::DropActions supportedDragActions() const override;

	virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

	virtual QStringList mimeTypes() const override;

	virtual QMimeData* mimeData(const QModelIndexList &indexes) const override;

	virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
								 int row, int column, const QModelIndex &parent) const override;
	virtual bool dropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

	MusicPlayer* player() const;
	void setPlayer(MusicPlayer* player);
public slots:
	void onCurrentIndexChanged(int oldIndex,int newIndex);
	void onInfoLoaded(int index);
	void refresh();
private:
	MusicPlayer* _player;
};

#endif // PLAYLISTMODEL_H
