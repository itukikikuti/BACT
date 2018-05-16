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
	Graphic();							//コンストラクタ
	Graphic(std::string filePath);		//コンストラクタ(ファイルパス)
	~Graphic();							//デストラクタ
	void Load(std::string filePath);	//画像をロードする
	int handle();						//ハンドルを取得する
	int width();						//widthを取得する
	int height();						//heightを取得する
};

class DivGraphic{
private:
	std::vector<int> graphicHandle;
	std::string filePath;
public:
	DivGraphic();																			//コンストラクタ
	DivGraphic(std::string filePath, const int AllNum, int XNum, int YNum, int XSize, int YSize);	//コンストラクタ(ファイルパス)
	~DivGraphic();																			//デストラクタ
	void Load(std::string filePath, const int AllNum, int XNum, int YNum, int XSize, int YSize);	//画像をロードする
	int handle(int i);																		//ハンドルを取得する
};