#include "DxLib.h"
#include "drawString.h"

//座標の中心に文字を表示する
void CenterDrawString(int x, int y, float centerX, float centerY, const char *string, int color, int edgeColor)
{
	DrawString(x - GetDrawStringWidth(string, strlen(string)) * centerX, y - GetFontSize() * centerY, string, color, edgeColor);
}
//座標の中心に文字を表示する
void CenterDrawStringToHandle(int x, int y, float centerX, float centerY, const char *string, int color, int fontHandle, int edgeColor)
{
	DrawStringToHandle(x - GetDrawStringWidthToHandle(string, strlen(string), fontHandle) * centerX, y - GetFontSizeToHandle(fontHandle) * centerY, string, color, fontHandle, edgeColor);
}
//文字を改行して表示する
void DrawLineString(int x, int y, const char *string, int color, int edgeColor)
{
	//フォントサイズを取得
	int fontSize = GetFontSize();

	//描画する文字列を用意する
	char tempString[256] = { 0 };
	sprintf_s(tempString, "%s", string);

	int charX = 0;
	int charY = 0;

	//1文字ずつ改行コードを見ながら描画する
	for (int i = 0; i < 256;)
	{
		//文字列が終了したら描画処理を抜ける
		if (tempString[i] == 0)
		{
			break;
		}
		//改行コードが来たら文字の描画位置を
		//改行した位置に変更する
		if (tempString[i] == 10)
		{
			charX = 0;
			charY += fontSize * 1.5;
			i += 1;
		}
		//文字を描画する
		else
		{
			if (tempString[i] < 0)
			{
				char tempChar[3] = { tempString[i], tempString[i + 1] };
				DrawString(x + charX, y + charY, tempChar, color, edgeColor);
				charX += GetDrawStringWidth(tempChar, strlen(tempChar));
				i += 2;
			}
			else
			{
				char tempChar[2] = { tempString[i] };
				DrawString(x + charX, y + charY, tempChar, color, edgeColor);
				charX += GetDrawStringWidth(tempChar, strlen(tempChar));
				i += 1;
			}
		}
	}

}

//文字を改行して表示する
extern void DrawLineStringToHandle(int x, int y, const char *string, int color, int fontHandle, int edgeColor)
{
	//描画する文字列を用意する
	char tempString[256] = { 0 };
	sprintf_s(tempString, "%s", string);

	int charX = 0;
	int charY = 0;

	//1文字ずつ改行コードを見ながら描画する
	for (int i = 0; i < 256;)
	{
		//文字列が終了したら描画処理を抜ける
		if (tempString[i] == 0)
		{
			break;
		}
		//改行コードが来たら文字の描画位置を
		//改行した位置に変更する
		if (tempString[i] == 10)
		{
			charX = 0;
			charY += GetFontSizeToHandle(fontHandle) * 1.5;
			i += 1;
		}
		//文字を描画する
		else
		{
			if (tempString[i] < 0)
			{
				char tempChar[3] = { tempString[i], tempString[i + 1] };
				DrawStringToHandle(x + charX, y + charY, tempChar, color, fontHandle, edgeColor);
				charX += GetDrawStringWidthToHandle(tempChar, strlen(tempChar), fontHandle);
				i += 2;
			}
			else
			{
				char tempChar[2] = { tempString[i] };
				DrawStringToHandle(x + charX, y + charY, tempChar, color, fontHandle, edgeColor);
				charX += GetDrawStringWidthToHandle(tempChar, strlen(tempChar), fontHandle);
				i += 1;
			}
		}
	}
}

//文字を1文字ずつ表示する
//文字を表示し終わったらtrueを返す
bool DrawSlowString(int x, int y, const char *string, int speed, int color, int edgeColor, bool reset)
{
	//描画する文字列を用意する
	char tempString[256] = { 0 };
	static int drawCharLength = 0;
	if (reset == true)drawCharLength = 0;

	for (int i = 0; i < 256; i++)
	{
		if (i < drawCharLength)tempString[i] = string[i];
		else tempString[i] = 0;
	}
	DrawLineString(x, y, tempString, color, edgeColor);

	static int wait = 0;
	if (string[drawCharLength] == 0)return true;
	if (string[drawCharLength] != 0 && wait == 0)
	{
		if (string[drawCharLength] < 0)drawCharLength += 2;
		else drawCharLength += 1;
	}
	if (wait < 0)wait = speed;
	else wait--;

	return false;
}
//文字を1文字ずつ表示する
//文字を表示し終わったらtrueを返す
bool DrawSlowStringToHandle(int x, int y, const char *string, int speed, int color, int fontHandle, int edgeColor, bool reset)
{
	//描画する文字列を用意する
	char tempString[256] = { 0 };
	static int drawCharLength = 0;
	static int wait = 0;
	if (reset == true)
	{
		drawCharLength = 0;
		wait = 0;
	}

	for (int i = 0; i < 256; i++)
	{
		if (i < drawCharLength)tempString[i] = string[i];
		else tempString[i] = 0;
	}
	DrawLineStringToHandle(x, y, tempString, color, fontHandle, edgeColor);

	if (string[drawCharLength] == 0)return true;
	if (string[drawCharLength] != 0 && wait == 0)
	{
		if (string[drawCharLength] < 0)drawCharLength += 2;
		else drawCharLength += 1;
	}
	if (wait < 0)wait = speed;
	else wait--;

	return false;
}