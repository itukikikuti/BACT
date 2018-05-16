#pragma once

extern void CenterDrawString(int x, int y, float centerX, float centerY, const char *string, int color, int edgeColor = 0);							//座標の中心に文字を表示する
extern void CenterDrawStringToHandle(int x, int y, float centerX, float centerY, const char *string, int color, int fontHandle, int edgeColor = 0);	//座標の中心に文字を表示する
extern void DrawLineString(int x, int y, const char *string, int color, int edgeColor = 0);															//文字を改行して表示する
extern void DrawLineStringToHandle(int x, int y, const char *string, int color, int fontHandle, int edgeColor = 0);									//文字を改行して表示する
extern bool DrawSlowString(int x, int y, const char *string, int speed, int color, int edgeColor = 0, bool reset = false);							//文字を1文字ずつ表示する。文字を表示し終わったらtrueを返す
extern bool DrawSlowStringToHandle(int x, int y, const char *string, int speed, int color, int fontHandle, int edgeColor = 0, bool reset = false);	//文字を1文字ずつ表示する。文字を表示し終わったらtrueを返す