#include "MusicUtil.h"
#include <XYZPlayer/MusicPlayer.h>
#include <XYZPlayer/MainContent.h>
#include <QDebug>

namespace MusicUtil{

LyricsError loadLyrics(MusicObject& music)
{
    music.lyrics.lyricList.clear();//clear old lyrics
    QFile file(music.lyrics.path);
    if(file.open(QFile::ReadOnly)){
        QMap<int64_t,QString> lyricsMap;
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
                    pos+=line.mid(1,colon-1).toLongLong()*60*1000;
                    pos+=line.mid(colon+1,closeBracket-colon-1).toDouble()*1000;
                    QString lyricsStr=line.mid(closeBracket+1);
                    if(lyricsMap.contains(pos)){
                        lyricsMap[pos].append(lyricsStr);
                    }else{
                        lyricsMap[pos]=lyricsStr;
                    }
                }else{
					music.lyrics.lyricList.clear();
                    return ParseError;
                }
            }else if(line[0]=='\n'){
                continue;
            }else{
				music.lyrics.lyricList.clear();
                return ParseError;
            }
        }
        for(QMap<int64_t,QString>::iterator it=lyricsMap.begin();it!=lyricsMap.end();++it){
            music.lyrics.lyricList.append(QPair<int64_t,QString>(it.key(),it.value()));
        }
        return NoError;
    }else{
		music.lyrics.lyricList.clear();
        return CannotOpenFile;
    }

	return NoError;
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

int loadPicture(MusicObject& music)
{
    AVFormatContext *fmt_ctx = NULL;
    int ret;

    //	av_register_all();

    if ((ret = avformat_open_input(&fmt_ctx,music.path.toLocal8Bit(), NULL, NULL))){
        //		char buffer[128];
        //		av_strerror(ret,buffer,sizeof(buffer));
        //		printf("Fail to open file at loadPicture AVError:%s\n",buffer);
        return ret;
    }
    if (fmt_ctx->iformat->read_header(fmt_ctx) < 0) {
        printf("No header format");
        return -1;
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
    return 0;
}

void savePlayerSetting(MusicPlayer* player)
{
    QSettings setting("../data/settings.ini",QSettings::IniFormat);
    setting.beginGroup("Player");
    setting.setValue("volume",qreal(player->audio()->volume()));
    setting.setValue("current_index",player->currentIndex());
    setting.setValue("playback_mode",qint32(player->playbackMode()));
    setting.endGroup();
}

void loadPlayerSetting(MusicPlayer* player)
{
    QSettings setting("../data/settings.ini",QSettings::IniFormat);
    player->audio()->setVolume(setting.value("Player/volume",qreal(1)).toReal());
    player->setCurrentIndex(setting.value("Player/current_index",-1).toInt());
    player->setPlaybackMode(PlaybackMode(setting.value("Player/playback_mode",qint32(Loop)).toInt()));
}

void saveMainWindowSetting(QWidget* window)
{
    QSettings setting("../data/settings.ini",QSettings::IniFormat);
    setting.beginGroup("MainWindow");
    setting.setValue("geometry",window->saveGeometry());
    setting.endGroup();
}

void loadMainWindowSetting(QWidget* window)
{
    QSettings setting("../data/settings.ini",QSettings::IniFormat);
    if(setting.contains("MainWindow/geometry"))
        window->restoreGeometry(setting.value("MainWindow/geometry").toByteArray());
}

void savePlaylist(MusicPlayer* player)
{
    QFile file("../data/playlist");
    if(file.open(QFile::WriteOnly)){
        QDataStream out(&file);
        out<<player->playlist();
    }
}

void loadPlaylist(MusicPlayer* player)
{
    QFile file("../data/playlist");
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
