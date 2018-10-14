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
#include <QStandardPaths>

class MusicPlayer;
class MainContent;

namespace MusicUtil{
enum LyricsError{
	NoError,
	CannotOpenFile,
	ParseError
};

void savePlayerSetting(MusicPlayer* player);
void loadPlayerSetting(MusicPlayer* player);

void saveMainWindowSetting(QWidget* window );
void loadMainWindowSetting(QWidget* window);

void savePlaylist(MusicPlayer* player );
void loadPlaylist(MusicPlayer* player);

LyricsError loadLyrics(MusicObject& music);
int loadInfo(MusicObject& music);
int loadPicture(MusicObject& music);

}

#endif
