#ifndef MUSICLOADER_H
#define MUSICLOADER_H

#include <QRunnable>
#include <QThreadPool>
#include <QMap>
#include <XYZPlayer/MusicObject.h>
#include <XYZPlayer/MusicUtil.h>

class MusicLoader;
class InfoLoader:public QRunnable
{
	public:
		InfoLoader(MusicObject* obj,MusicLoader* loader);
		void run();
	private:
		MusicObject* _obj;
		MusicLoader* _loader;
};
class PictureLoader:public QRunnable
{
	public:
		PictureLoader(MusicObject* obj,MusicLoader* loader);
		void run();
	private:
		MusicObject* _obj;
		MusicLoader* _loader;
};
class LyricsLoader:public QRunnable
{
	public:
		LyricsLoader(MusicObject* obj,MusicLoader* loader);
		void run();
	private:
		MusicObject* _obj;
		MusicLoader* _loader;
};


class MusicLoader : public QObject
{
		Q_OBJECT
	public:
		explicit MusicLoader(QObject *parent = nullptr);

		void asyncLoadInfo(MusicObject* obj);
		void asyncLoadPicture(MusicObject* obj);
		void asyncLoadLyrics(MusicObject* obj);

		void unLoadInfo(MusicObject* obj);
		void unLoadPicture(MusicObject* obj);
		void unLoadLyrics(MusicObject* obj);

		void remove(MusicObject* obj);
	signals:
		void infoLoaded(MusicObject*);
		void pictureLoaded(MusicObject*);
		void lyricsLoaded(MusicObject*);
	protected:
		QMap<MusicObject*,QRunnable*> _loaders;
};

#endif // MUSICLOADER_H
