#pragma once

#include <string>

class Sound{
private:
	int handle;
	unsigned char volume;
	std::string filePath;
public:
	Sound();																	//コンストラクタ
	Sound(std::string filePath);												//コンストラクタ(ファイルパス)
	Sound(std::string filePath, bool playFlag, unsigned char volume = 255, int playType = DX_PLAYTYPE_BACK);	//コンストラクタ(ファイルパス,プレイフラグ,プレイタイプ)
	~Sound();																	//デストラクタ
	void Load(std::string filePath);											//サウンドをロードする
	int Handle();
	unsigned char Volume();
	void Volume(unsigned char volume);
	void Play(int playType, unsigned char volume = 255, int playPosition = 0);
	void Stop();
};
