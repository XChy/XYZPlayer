#ifndef SONGLISTMODEL_H
#define SONGLISTMODEL_H

#include <QAbstractTableModel>
#include <QMimeData>
#include <XYZPlayer/Songlist.h>

class SonglistModel : public QAbstractTableModel
{
		Q_OBJECT

	public:
		explicit SonglistModel(QObject *parent = nullptr);

		int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		int columnCount(const QModelIndex &parent = QModelIndex()) const override;

		virtual QVariant headerData(int section, Qt::Orientation orientation,
										int role = Qt::DisplayRole) const override;

		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

		virtual Qt::DropActions supportedDropActions() const override;
		virtual Qt::DropActions supportedDragActions() const override;

		virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

		virtual QStringList mimeTypes() const override;

		virtual QMimeData* mimeData(const QModelIndexList &indexes) const override;

		virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
									 int row, int column, const QModelIndex &parent) const override;
		virtual bool dropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

		void refresh();

		Songlist* songlist() const;
		void setSonglist(Songlist* songlist);
	private:
		Songlist* _songlist;
};

#endif // SONGLISTMODEL_H
