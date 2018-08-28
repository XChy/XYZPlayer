#include "MusicUtil.h"
#include <XYZPlayer/MusicPlayer.h>

namespace MusicUtil{

LyricsError loadLyrics(MusicObject& music)
{
	QFile file(music.d->lyrics.path);
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
					music.d->lyrics.lyricList.append(QPair<int64_t,QString>(pos,lyricsStr));
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

void loadInfo(MusicObject& music)
{
	AVFormatContext *fmt_ctx = NULL;
	AVDictionaryEntry *tag = NULL;
	int ret;

	av_register_all();

	if ((ret = avformat_open_input(&fmt_ctx, music.d->path.toLocal8Bit(), NULL, NULL))){
		char buffer[128];
		av_strerror(ret,buffer,sizeof(buffer));
		printf("Fail to open file at loadInfo AVError:%s\n",buffer);
		return;
	}

	avformat_find_stream_info(fmt_ctx, NULL);
	music.d->duration=fmt_ctx->duration;

	while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
		music.d->infoTags[QString(tag->key).toLower()]=tag->value;
	}

	if(!music.d->infoTags.contains("title")){
		music.d->infoTags["title"]=QFileInfo(music.d->path).baseName();
	}

	avformat_close_input(&fmt_ctx);
	avformat_free_context(fmt_ctx);
}

void loadPicture(MusicObject& music)
{
	AVFormatContext *fmt_ctx = NULL;
	int ret;

	av_register_all();

	if ((ret = avformat_open_input(&fmt_ctx,music.d->path.toLocal8Bit(), NULL, NULL))){
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
			music.d->picture = QImage::fromData((uchar*)pkt.data, pkt.size);
			break;
		}
	}

	avformat_close_input(&fmt_ctx);
	avformat_free_context(fmt_ctx);
}

void savePlayerSetting(MusicPlayer* player, QString path)
{
	QSettings setting(path,QSettings::IniFormat);
	setting.beginGroup("");
	setting.setValue("volume",qreal(player->audio()->volume()));
//	setting.setValue("current_index",qint32(player->currentIndex()));
	setting.setValue("playback_mode",qint32(player->playbackMode()));
}

void loadPlayerSetting(MusicPlayer* player, QString path)
{
	QSettings setting(path,QSettings::IniFormat);
	player->audio()->setVolume(setting.value("volume",qreal(1)).toReal());
//	player->setCurrentIndex(setting.value("current_index",qint32(-1)).toInt());
	player->setPlaybackMode(PlaybackMode(setting.value("playback_mode",qint32(Loop)).toInt()));
}

}
