#include <string>
#include "DxLib.h"
#include "sound.h"
using namespace std;

//コンストラクタ
Sound::Sound()
{
	Sound::handle = -1;
	Sound::volume = 255;
}
//コンストラクタ(ファイルパス)
Sound::Sound(std::string filePath)
{
	Sound::Load(filePath);
	Sound::volume = 255;
}
//コンストラクタ(ファイルパス)
Sound::Sound(std::string filePath, bool playFlag, unsigned char volume, int playType)
{
	Sound::Load(filePath);
	Sound::volume = volume;
	if (playFlag){ Sound::Play(playType); }
}
//デストラクタ
Sound::~Sound()
{

}
//サウンドをロードする
void Sound::Load(std::string filePath)
{
	Sound::filePath = filePath;
	Sound::handle = LoadSoundMem(Sound::filePath.c_str());
}
int Sound::Handle()
{
	return Sound::handle;
}
unsigned char Sound::Volume()
{
	return Sound::volume;
}
void Sound::Volume(unsigned char volume)
{
	Sound::volume = volume;
	ChangeVolumeSoundMem(volume, handle);
}
void Sound::Play(int playType, unsigned char volume, int playPosition)
{
	Sound::Volume(volume);
	if (CheckSoundMem(Sound::handle) == false)
	{
		SetCurrentPositionSoundMem(playPosition, Sound::handle);
		PlaySoundMem(Sound::handle, playType, false);
	}
}
void Sound::Stop()
{
	StopSoundMem(Sound::handle);
}
