#pragma once

#include <string>
#include <vector>

class Graphic{
private:
	int graphicHandle;
	std::string filePath;
	int x;
	int y;
	int oldScreenX;
public:
	Graphic();							//�R���X�g���N�^
	Graphic(std::string filePath);		//�R���X�g���N�^(�t�@�C���p�X)
	~Graphic();							//�f�X�g���N�^
	void Load(std::string filePath);	//�摜�����[�h����
	int handle();						//�n���h�����擾����
	int width();						//width���擾����
	int height();						//height���擾����
};

class DivGraphic{
private:
	std::vector<int> graphicHandle;
	std::string filePath;
public:
	DivGraphic();																			//�R���X�g���N�^
	DivGraphic(std::string filePath, const int AllNum, int XNum, int YNum, int XSize, int YSize);	//�R���X�g���N�^(�t�@�C���p�X)
	~DivGraphic();																			//�f�X�g���N�^
	void Load(std::string filePath, const int AllNum, int XNum, int YNum, int XSize, int YSize);	//�摜�����[�h����
	int handle(int i);																		//�n���h�����擾����
};