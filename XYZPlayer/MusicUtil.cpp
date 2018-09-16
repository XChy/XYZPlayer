#include "MusicUtil.h"
#include <XYZPlayer/MusicPlayer.h>
#include <XYZPlayer/MainWindow.h>
#include <QDebug>

namespace MusicUtil{

LyricsError loadLyrics(MusicObject& music)
{
	music.lyrics.lyricList.clear();//clear old lyrics

	QFile file(music.lyrics.path);
	if(file.open(QFile::ReadOnly)){
		while(!file.atEnd()){
			QString line=file.readLine();
			if(line[0]=='['){
				int closeBracket=line.indexOf(']');
				if(closeBracket){
					if(!line[1].isDigit()){
						continue;
					}
					int colon=line.indexOf(':');
					int64_t pos=0;
					pos+=line.mid(1,colon-1).toLongLong()*60*1000*1000;
					pos+=line.mid(colon+1,closeBracket-colon-1).toDouble()*1000*1000;
					QString lyricsStr=line.mid(closeBracket+1);
					music.lyrics.lyricList.append(QPair<int64_t,QString>(pos,lyricsStr));
				}else{
					return ParseError;
				}
			}else if(line[0]=='\n'){
				continue;
			}else{
				return ParseError;
			}
		}
		return NoError;
	}else{
		return CannotOpenFile;
	}
}

int loadInfo(MusicObject& music)
{
	AVFormatContext *fmt_ctx = NULL;
	AVDictionaryEntry *tag = NULL;
	int ret;

	av_register_all();

	if (ret = avformat_open_input(&fmt_ctx, music.path.toLocal8Bit(), NULL, NULL)){
//		char buffer[128];
//		av_strerror(ret,buffer,sizeof(buffer));
//		printf("Fail to open file at loadInfo AVError:%s\n",buffer);
		return ret;
	}

	avformat_find_stream_info(fmt_ctx, NULL);
	music.duration=fmt_ctx->duration;

	while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
		music.infoTags[QString(tag->key).toLower()]=tag->value;
	}

	if(!music.infoTags.contains("title")){
		music.infoTags["title"]=QFileInfo(music.path).baseName();
	}else if(music.infoTags["title"].isEmpty()){
		music.infoTags["title"]=QFileInfo(music.path).baseName();
	}

	avformat_close_input(&fmt_ctx);
	avformat_free_context(fmt_ctx);
	return 0;
}

void loadPicture(MusicObject& music)
{
	AVFormatContext *fmt_ctx = NULL;
	int ret;

	av_register_all();

	if ((ret = avformat_open_input(&fmt_ctx,music.path.toLocal8Bit(), NULL, NULL))){
		char buffer[128];
		av_strerror(ret,buffer,sizeof(buffer));
		printf("Fail to open file at loadPicture AVError:%s\n",buffer);
		return;
	}
	if (fmt_ctx->iformat->read_header(fmt_ctx) < 0) {
		printf("No header format");
		return;
	}

	for (int i = 0; i < fmt_ctx->nb_streams; i++){
		if (fmt_ctx->streams[i]->disposition & AV_DISPOSITION_ATTACHED_PIC) {
			AVPacket pkt = fmt_ctx->streams[i]->attached_pic;
			music.picture.loadFromData((uchar*)pkt.data, pkt.size);
			break;
		}
	}

	avformat_close_input(&fmt_ctx);
	avformat_free_context(fmt_ctx);
}

void savePlayerSetting(MusicPlayer* player, QString path)
{
	QSettings setting(path,QSettings::IniFormat);
	setting.beginGroup("Player");
	setting.setValue("volume",qreal(player->audio()->volume()));
	setting.setValue("current_index",player->currentIndex());
	setting.setValue("playback_mode",qint32(player->playbackMode()));
	setting.endGroup();
}

void loadPlayerSetting(MusicPlayer* player, QString path)
{
	QSettings setting(path,QSettings::IniFormat);
	player->audio()->setVolume(setting.value("Player/volume",qreal(1)).toReal());
	player->setCurrentIndex(setting.value("Player/current_index",-1).toInt());
	player->setPlaybackMode(PlaybackMode(setting.value("Player/playback_mode",qint32(Loop)).toInt()));
}

void saveMainWindowSetting(MainWindow* window, QString path)
{
	QSettings setting(path,QSettings::IniFormat);
	setting.beginGroup("MainWindow");
	setting.setValue("size",window->size());
	setting.setValue("pos",window->pos());
	setting.endGroup();
}

void loadMainWindowSetting(MainWindow* window, QString path)
{
	QSettings setting(path,QSettings::IniFormat);
	window->resize(setting.value("MainWindow/size",window->size()).toSize());
	window->move(setting.value("MainWindow/pos",window->pos()).toPoint());
}

void savePlaylist(MusicPlayer* player, QString path)
{
	QFile file(path);
	if(file.open(QFile::WriteOnly)){
		QDataStream out(&file);
		out<<player->playlist();
	}
}

void loadPlaylist(MusicPlayer* player, QString path)
{
	QFile file(path);
	if(file.open(QFile::ReadWrite)){
		QDataStream stream(&file);
		if(!file.exists()){
			stream<<QList<MusicObject>();
			return;
		}
		if(!stream.atEnd()){
			stream>>player->playlist();
		}
	}
}


}
