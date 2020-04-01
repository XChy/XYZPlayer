#include "SonglistsModel.h"

SonglistsModel::SonglistsModel(QObject *parent)
	: QAbstractListModel(parent),
	  _songlists(nullptr)
{
}

int SonglistsModel::rowCount(const QModelIndex& parent) const
{
	if(parent.isValid()||!_songlists)
		return 0;

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
	return {"text/url-list","XYZPlayer/Songlist","XYZPlayer/MusiclistAndIndexes"};
}

QMimeData* SonglistsModel::mimeData(const QModelIndexList& indexes) const
{
	QMimeData* data=new QMimeData;
	data->setData("XYZPlayer/Songlist",QByteArray::number(qulonglong(&_songlists->at(indexes.first().row()))));

	QByteArray array;
	QDataStream stream(&array,QIODevice::WriteOnly);
	const Songlist& list=_songlists->at(indexes.first().row());
	stream<<(qulonglong)&list;
	stream<<list.size();
	for(int i=0;i<list.size();++i){
		stream<<i;
	}
	data->setData("XYZPlayer/MusiclistAndIndexes",array);
	//Copy the pointer of songlist
	return data;
}

bool SonglistsModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) const
{
	return data->hasUrls()
			||data->hasFormat("XYZPlayer/MusiclistAndIndexes")
			||data->hasFormat("XYZPlayer/Songlist");
}

bool SonglistsModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
	qDebug()<<"Drop in Songlists"<<row<<", Parent"<<parent;
	if (action == Qt::IgnoreAction)
		return true;

	if(!_songlists)
		return true;

	int insertIndex;
	if (row != -1 && !(row>=rowCount()) )
		insertIndex = row;
	else if (parent.isValid())
		insertIndex = parent.row();
	else
		insertIndex = rowCount()-1;

	qDebug()<<"Insert in Songlists"<<insertIndex;

	if(data->hasFormat("XYZPlayer/Songlist")){
		qDebug()<<"Drop songlist in songlists";
		Songlist* songlist=(Songlist*)data->data("XYZPlayer/Songlist").toULongLong();
		_songlists->move(_songlists->indexOf(*songlist),insertIndex);
		return true;
	}
	//BUG only receive row=0
	if(data->hasFormat("XYZPlayer/MusiclistAndIndexes")){
		qDebug()<<"Drop indexes in songlists";
		QByteArray _data=data->data("XYZPlayer/MusiclistAndIndexes");
		QDataStream stream(&_data,QIODevice::ReadOnly);
		QList<MusicObject>* list;
		int size;
		stream>>(qulonglong&)list;
		stream>>size;//TODO sort order
		for(int i=0;i<size;++i){
			int index;
			stream>>index;
			_songlists->operator[](insertIndex).insert(0,list->at(index));
			if(_songlists->operator[](insertIndex).operator[](0).picture.isNull())
				MusicUtil::loadPicture(_songlists->operator[](insertIndex).operator[](0));
		}
		refresh();
		return true;
	}
	return QAbstractListModel::dropMimeData(data,action,row,column,parent);
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
	refresh();
}

