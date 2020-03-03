#include "MusicLoader.h"

InfoLoader::InfoLoader(MusicObject* obj, MusicLoader* loader)
	:_obj(obj),_loader(loader)
{
	setAutoDelete(true);
}

void InfoLoader::run()
{
	MusicUtil::loadInfo(*_obj);
	_loader->remove(_obj);
	emit _loader->infoLoaded(_obj);
}

PictureLoader::PictureLoader(MusicObject* obj, MusicLoader* loader)
	:_obj(obj),_loader(loader)
{
	setAutoDelete(true);
}

void PictureLoader::run()
{
	MusicUtil::loadPicture(*_obj);
	_loader->remove(_obj);
	emit _loader->pictureLoaded(_obj);
}


LyricsLoader::LyricsLoader(MusicObject* obj, MusicLoader* loader)
	:_obj(obj),_loader(loader)
{
	setAutoDelete(true);
}

void LyricsLoader::run()
{
	MusicUtil::loadLyrics(*_obj);
	_loader->remove(_obj);
	emit _loader->lyricsLoaded(_obj);
}

MusicLoader::MusicLoader(QObject *parent) : QObject(parent)
{

}

void MusicLoader::asyncLoadInfo(MusicObject* obj)
{
	QRunnable* loader=new InfoLoader(obj,this);
	_loaders[obj]=loader;
	QThreadPool::globalInstance()->start(loader);
}

void MusicLoader::asyncLoadPicture(MusicObject* obj)
{
	QRunnable* loader=new PictureLoader(obj,this);
	_loaders[obj]=loader;
	QThreadPool::globalInstance()->start(loader);
}

void MusicLoader::asyncLoadLyrics(MusicObject* obj)
{
	QRunnable* loader=new LyricsLoader(obj,this);
	_loaders[obj]=loader;
	QThreadPool::globalInstance()->start(loader);
}

void MusicLoader::unLoadInfo(MusicObject* obj)
{
	remove(obj);
	obj->duration=0;
	obj->infoTags.clear();
}

void MusicLoader::unLoadPicture(MusicObject* obj)
{
	remove(obj);
	obj->picture=QPixmap();
}

void MusicLoader::unLoadLyrics(MusicObject* obj)
{
	remove(obj);
	obj->lyrics.lyricList.clear();
}

void MusicLoader::remove(MusicObject* obj)
{
	if(_loaders.contains(obj)){
		if(!QThreadPool::globalInstance()->tryTake(_loaders[obj])){
			//Warning
		}
		_loaders.remove(obj);
	}
}


