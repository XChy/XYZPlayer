#ifndef SONGLISTSMODEL_H
#define SONGLISTSMODEL_H

#include <QAbstractListModel>
#include <QMimeData>
#include <QIcon>
#include <XYZPlayer/Songlist.h>
#include <XYZPlayer/MusicLoader.h>

class SonglistsModel : public QAbstractListModel
{
		Q_OBJECT
	public:
		SonglistsModel(QObject* parent=nullptr);

		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

		virtual Qt::DropActions supportedDropActions() const;
		virtual Qt::DropActions supportedDragActions() const;

		virtual Qt::ItemFlags flags(const QModelIndex &index) const;

		virtual QStringList mimeTypes() const;

		virtual QMimeData* mimeData(const QModelIndexList &indexes) const;

		virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
									 int row, int column, const QModelIndex &parent) const;
		virtual bool dropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent);

		virtual bool setData(const QModelIndex& index, const QVariant& v, int role = Qt::EditRole);

		void refresh();

		Songlists* songlists() const;
		void setSonglists(Songlists* songlists);
	public slots:
//		void onPictureLoaded(int index);
	private:
		Songlists* _songlists;

};

#endif // SONGLISTSMODEL_H
