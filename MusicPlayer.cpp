#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
	:mCurrentIndex(-1),
	  mPlaybackMode(Loop)
{
	connect(this,&MusicPlayer::mediaStatusChanged,this,&MusicPlayer::onMediaStatusChanged);
}

QList<MusicObject> MusicPlayer::playlist() const
{
	return mPlaylist;
}

void MusicPlayer::setPlaylist(const QList<MusicObject>& playlist)
{
	mPlaylist = playlist;
}


PlaybackMode MusicPlayer::playbackMode() const
{
	return mPlaybackMode;
}

void MusicPlayer::setPlaybackMode(const PlaybackMode& playbackMode)
{
	mPlaybackMode = playbackMode;
}

int MusicPlayer::currentIndex() const
{
	return mCurrentIndex;
}

void MusicPlayer::setCurrentIndex(int currentIndex)
{
	mCurrentIndex = currentIndex;
	setFile(currentMusic().path);
	emit currentIndexChanged(currentIndex);
}

MusicObject& MusicPlayer::currentMusic()
{
	return mPlaylist[mCurrentIndex];
}

void MusicPlayer::addMusic(const MusicObject& obj)
{
	mPlaylist.append(obj);
}

void MusicPlayer::addMusicToCurrent(const MusicObject& obj)
{
	addMusic(obj);
	setCurrentIndex(mPlaylist.size()-1);
}

void MusicPlayer::playAt(int index)
{
	stop();
	setCurrentIndex(index);
	play();
}

void MusicPlayer::playNext()
{
	if(!mPlaylist.isEmpty()){
		playAt( mCurrentIndex!=mPlaylist.size()-1 ? mCurrentIndex+1 : 0 );
	}
}

void MusicPlayer::playPrev()
{
	if(!mPlaylist.isEmpty()){
		playAt( mCurrentIndex!=0 ? mCurrentIndex-1 : mPlaylist.size()-1 );
	}
}

void MusicPlayer::playback()
{
	switch (mPlaybackMode) {
		case Loop:
			playNext();
			break;
		case CurrentItemLoop:
			playAt(mCurrentIndex);
			break;
		case Sequential:
			if(mCurrentIndex!=mPlaylist.size()-1){
				playAt(mCurrentIndex+1);
			}
			break;
		case Random:
			if(!mPlaylist.isEmpty()){
				playAt(qrand()%mPlaylist.size());
			}
			break;
	}
}

bool MusicPlayer::canPlayback()
{
	switch (mPlaybackMode) {
		case Loop:
		case CurrentItemLoop:
		case Random:
			return !mPlaylist.isEmpty();

		case Sequential:
			return mCurrentIndex!=mPlaylist.size()-1;
	}
}

void MusicPlayer::loadInfo(int index)
{
	AVFormatContext *fmt_ctx = NULL;
	AVDictionaryEntry *tag = NULL;
	int ret;

	av_register_all();

	if ((ret = avformat_open_input(&fmt_ctx, mPlaylist[index].path.toLocal8Bit(), NULL, NULL))){
		printf("Fail to open file");
	}

	//读取metadata中所有的tag
	while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
		mPlaylist[index].info[tag->key]=tag->value;
	}
	emit loadedInfo(index);
}

void MusicPlayer::loadPicture(int index)
{
	AVFormatContext *fmt_ctx = NULL;
	AVDictionaryEntry *tag = NULL;
	int ret;

	av_register_all();

	if ((ret = avformat_open_input(&fmt_ctx,mPlaylist[index].path.toLocal8Bit(), NULL, NULL))){
		printf("Fail to open file");
	}

	if (fmt_ctx->iformat->read_header(fmt_ctx) < 0) {
		printf("No header format");
		return;
	}

	for (int i = 0; i < fmt_ctx->nb_streams; i++){
		if (fmt_ctx->streams[i]->disposition & AV_DISPOSITION_ATTACHED_PIC) {
			AVPacket pkt = fmt_ctx->streams[i]->attached_pic;
			//使用QImage读取完整图片数据（注意，图片数据是为解析的文件数据，需要用QImage::fromdata来解析读取）
			mPlaylist[index].picture = QImage::fromData((uchar*)pkt.data, pkt.size);
			break;
		}
	}
	emit loadedPicture(index);
}

void MusicPlayer::onMediaStatusChanged(QtAV::MediaStatus state)
{
	if(state==QtAV::EndOfMedia){
		playback();
	}
}



