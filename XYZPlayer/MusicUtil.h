#ifndef MUSICUTIL_H
#define MUSICUTIL_H

#include <QFileInfo>
extern "C"{
#include <libavformat/avformat.h>
}
#include <XYZPlayer/MusicObject.h>
#include <QSettings>

class MusicPlayer;

namespace MusicUtil{
enum LyricsError{
	NoError,
	CannotOpenFile,
	ParseError
};

void savePlayerSetting(MusicPlayer* player ,QString path);
void loadPlayerSetting(MusicPlayer* player ,QString path);

void saveMainWindowSetting(MusicPlayer* player ,QString path);
void loadMainSetting(MusicPlayer* player ,QString path);

void savePlaylist(MusicPlayer* player ,QString path);//TODO complele it
void loadPlaylist(MusicPlayer* player ,QString path);//TODO complele it

LyricsError loadLyrics(MusicObject& music);
void loadInfo(MusicObject& music);
void loadPicture(MusicObject& music);

}

#endif
