#include "SonglistsModel.h"

SonglistsModel::SonglistsModel(QObject *parent)
	: QAbstractListModel(parent)
{
}

int SonglistsModel::rowCount(const QModelIndex& parent) const
{
	return _songlists->size();
}

QVariant SonglistsModel::data(const QModelIndex& index, int role) const
{

	if(!index.isValid()){
		return QVariant();
	}

	const Songlist& songlist = _songlists->at(index.row());
	if(role==Qt::DisplayRole)
		return songlist.name();
	else if(role==Qt::DecorationRole){
		if(songlist.isEmpty()||songlist.first().picture.isNull()){
			return QIcon(QPixmap(":/images/easy/folder.png"));
		}else{
			return QIcon(songlist.first().picture);
		}
	}
	return QVariant();
}

Qt::DropActions SonglistsModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

Qt::DropActions SonglistsModel::supportedDragActions() const
{
	return Qt::MoveAction;
}

Qt::ItemFlags SonglistsModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);
	return Qt::ItemIsDropEnabled| Qt::ItemIsDragEnabled | defaultFlags;
}

QStringList SonglistsModel::mimeTypes() const
{
	return {"text/url-list","XYZPlayer/MusiclistAndIndexes"};
}

QMimeData* SonglistsModel::mimeData(const QModelIndexList& indexes) const
{
	QMimeData* data=new QMimeData;
	return data;
}

bool SonglistsModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) const
{
	return data->hasUrls()||data->hasFormat("XYZPlayer/MusiclistAndIndexes")||data->hasFormat("XYZPlayer/Songlist");
}

bool SonglistsModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
	return QAbstractListModel::dropMimeData(data,action,row,column,parent);
}

bool SonglistsModel::setData(const QModelIndex& index, const QVariant& v, int role)
{
	return QAbstractListModel::setData(index,v,role);
}

void SonglistsModel::refresh()
{
	beginResetModel();
	endResetModel();
}



Songlists* SonglistsModel::songlists() const
{
	return _songlists;
}

void SonglistsModel::setSonglists(Songlists* songlist)
{
	_songlists = songlist;
	beginResetModel();
	endResetModel();
}

