#pragma once

#include <string>

class Sound{
private:
	int handle;
	unsigned char volume;
	std::string filePath;
public:
	Sound();																	//�R���X�g���N�^
	Sound(std::string filePath);												//�R���X�g���N�^(�t�@�C���p�X)
	Sound(std::string filePath, bool playFlag, unsigned char volume = 255, int playType = DX_PLAYTYPE_BACK);	//�R���X�g���N�^(�t�@�C���p�X,�v���C�t���O,�v���C�^�C�v)
	~Sound();																	//�f�X�g���N�^
	void Load(std::string filePath);											//�T�E���h�����[�h����
	int Handle();
	unsigned char Volume();
	void Volume(unsigned char volume);
	void Play(int playType, unsigned char volume = 255, int playPosition = 0);
	void Stop();
};
