#include <string>
#include "DxLib.h"
#include "main.h"
#include "graphic.h"
using namespace std;

//コンストラクタ
Graphic::Graphic()
{
	Graphic::graphicHandle = -1;
	Graphic::x = 0;
	Graphic::y = 0;
	Graphic::oldScreenX = screenX;
}
//コンストラクタ(ファイルパス)
Graphic::Graphic(string filePath)
{
	Graphic::filePath = filePath;
	Graphic::graphicHandle = LoadGraph(Graphic::filePath.c_str());
	GetGraphSize(Graphic::graphicHandle, &(Graphic::x), &(Graphic::y));
	Graphic::oldScreenX = screenX;
}
//デストラクタ
Graphic::~Graphic()
{
	DeleteGraph(Graphic::graphicHandle);
	Graphic::graphicHandle = -1;
	Graphic::filePath = "";
	Graphic::x = 0;
	Graphic::y = 0;
}
//画像をロードする
void Graphic::Load(string filePath)
{
	Graphic::filePath = filePath;
	Graphic::graphicHandle = LoadGraph(Graphic::filePath.c_str());
	GetGraphSize(Graphic::graphicHandle, &(Graphic::x), &(Graphic::y));
}
//ハンドルを取得する
int Graphic::handle()
{
	//もし画面サイズが変わっていたら
	//ハンドルが削除されているので
	//画像をロードしなおします
	if (screenX != Graphic::oldScreenX)
	{
		Graphic::Load(Graphic::filePath);
	}

	Graphic::oldScreenX = screenX;

	return (Graphic::graphicHandle);
}
//widthを取得する
int Graphic::width()
{
	return (Graphic::x);
}
//heightを取得する
int Graphic::height()
{
	return (Graphic::y);
}

//コンストラクタ
DivGraphic::DivGraphic()
{

}
//コンストラクタ(ファイルパス)
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
//デストラクタ
DivGraphic::~DivGraphic()
{

}
//画像をロードする
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
//ハンドルを取得する
int DivGraphic::handle(int i)
{
	return DivGraphic::graphicHandle[i];
}