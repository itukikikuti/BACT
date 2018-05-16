#include <string>
#include "DxLib.h"
#include "main.h"
#include "graphic.h"
using namespace std;

//�R���X�g���N�^
Graphic::Graphic()
{
	Graphic::graphicHandle = -1;
	Graphic::x = 0;
	Graphic::y = 0;
	Graphic::oldScreenX = screenX;
}
//�R���X�g���N�^(�t�@�C���p�X)
Graphic::Graphic(string filePath)
{
	Graphic::filePath = filePath;
	Graphic::graphicHandle = LoadGraph(Graphic::filePath.c_str());
	GetGraphSize(Graphic::graphicHandle, &(Graphic::x), &(Graphic::y));
	Graphic::oldScreenX = screenX;
}
//�f�X�g���N�^
Graphic::~Graphic()
{
	DeleteGraph(Graphic::graphicHandle);
	Graphic::graphicHandle = -1;
	Graphic::filePath = "";
	Graphic::x = 0;
	Graphic::y = 0;
}
//�摜�����[�h����
void Graphic::Load(string filePath)
{
	Graphic::filePath = filePath;
	Graphic::graphicHandle = LoadGraph(Graphic::filePath.c_str());
	GetGraphSize(Graphic::graphicHandle, &(Graphic::x), &(Graphic::y));
}
//�n���h�����擾����
int Graphic::handle()
{
	//������ʃT�C�Y���ς���Ă�����
	//�n���h�����폜����Ă���̂�
	//�摜�����[�h���Ȃ����܂�
	if (screenX != Graphic::oldScreenX)
	{
		Graphic::Load(Graphic::filePath);
	}

	Graphic::oldScreenX = screenX;

	return (Graphic::graphicHandle);
}
//width���擾����
int Graphic::width()
{
	return (Graphic::x);
}
//height���擾����
int Graphic::height()
{
	return (Graphic::y);
}

//�R���X�g���N�^
DivGraphic::DivGraphic()
{

}
//�R���X�g���N�^(�t�@�C���p�X)
DivGraphic::DivGraphic(std::string filePath, const int AllNum, int XNum, int YNum, int XSize, int YSize)
{
	DivGraphic::filePath = filePath;
	DivGraphic::graphicHandle.resize(AllNum);
	int *tempHandle = new int[AllNum];
	LoadDivGraph(filePath.c_str(), AllNum, XNum, YNum, XSize, YSize, tempHandle);
	for (int i = 0; i < AllNum; i++)
	{
		DivGraphic::graphicHandle[i] = tempHandle[i];
	}
}
//�f�X�g���N�^
DivGraphic::~DivGraphic()
{

}
//�摜�����[�h����
void DivGraphic::Load(std::string filePath, const int AllNum, int XNum, int YNum, int XSize, int YSize)
{
	DivGraphic::filePath = filePath;
	DivGraphic::graphicHandle.resize(AllNum);
	int *tempHandle = new int[AllNum];
	LoadDivGraph(filePath.c_str(), AllNum, XNum, YNum, XSize, YSize, tempHandle);
	for (int i = 0; i < AllNum; i++)
	{
		DivGraphic::graphicHandle[i] = tempHandle[i];
	}
}
//�n���h�����擾����
int DivGraphic::handle(int i)
{
	return DivGraphic::graphicHandle[i];
}