#ifndef MUSICUTIL_H
#define MUSICUTIL_H

#include <QFileInfo>
extern "C"{
#include <libavformat/avformat.h>
}
#include <XYZPlayer/MusicObject.h>
#include <QSettings>
#include <QDataStream>
#include <QFile>

class MusicPlayer;
class MainWindow;

namespace MusicUtil{
enum LyricsError{
	NoError,
	CannotOpenFile,
	ParseError
};

void savePlayerSetting(MusicPlayer* player ,QString path);
void loadPlayerSetting(MusicPlayer* player ,QString path);

void saveMainWindowSetting(MainWindow* window ,QString path);
void loadMainWindowSetting(MainWindow* window ,QString path);

void savePlaylist(MusicPlayer* player ,QString path);
void loadPlaylist(MusicPlayer* player ,QString path);

LyricsError loadLyrics(MusicObject& music);
int loadInfo(MusicObject& music);
void loadPicture(MusicObject& music);

}

#endif
