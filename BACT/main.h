#pragma once

#include "input.h"
#include "graphic.h"
#include "gameState.h"

#define SCREEN_X 1280
#define SCREEN_Y 960
#define GetRadian(angle) ((angle)*DX_PI/180)
#define GetArrayLength(array) (sizeof(array)/sizeof(array[0]))

enum FontSize{
	FS_8,
	FS_12,
	FS_16,
	FS_24,
	FS_32,
	FS_48,
	FS_64,
	FS_96,
	FS_MAX,
};

extern int screenX;
extern int screenY;
extern Input key;
extern int fontHandle[FS_MAX];
extern bool gameEndFlag;
extern GameState gameState;

//CSVファイルから行列を指定してその行列のデータを文字列として吐き出す
extern void LoadCSV(char *string, const char *fileName, int row, int column, int rowMax, int columnMax);
//カーソルを描画する
extern void DrawCursor(int x1, int y1, int x2, int y2, bool up, bool down, bool left, bool right);
//ロード画面を描画する
extern void DrawLoad();
//画面サイズを変更します
extern void ChangeScreenSize(int x, int y);
//2点間の距離を求める
extern int CheckDistance(double x1, double y1, double x2, double y2);
//円同士の当たり判定です
extern bool CheckHitCircleAndCircle(int x1, int y1, double r1, int x2, int y2, double r2);