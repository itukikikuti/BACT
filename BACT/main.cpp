/*
2014/12/28
BACT新ソースコード
*/
#include "DxLib.h"
#include <math.h>
#include "main.h"
#include "drawString.h"
#include "resource.h"

int screenX = 800;
int screenY = 600;
Input key;
int fontHandle[FS_MAX];
bool gameEndFlag = false;
int screen;
GameState gameState(GAME_STATE_LOGO);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//コンソール呼び出し
	if (true)AllocConsole(); FILE* fp; freopen_s(&fp, "CONOUT$", "w", stdout); freopen_s(&fp, "CONIN$", "r", stdin);

	//アイコンをセットする
	SetWindowIconID(IDI_MYICON);

	//しねきゃぷしょんフォントをロードする
	LPCSTR fontPath = "data/font/cinecaption2.28.ttf";
	AddFontResourceEx(fontPath, FR_PRIVATE, NULL);

	//ウィンドウのタイトルをセットする
	SetMainWindowText("BACT");
	//ウィンドウのサイズを設定する
	SetGraphMode(screenX, screenY, 32);
	//ウィンドウモードで起動する
	ChangeWindowMode(true);
	//ログ出力を行わない
	SetOutApplicationLogValidFlag(false);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)return -1;

	//裏画面に描画する
	SetDrawScreen(DX_SCREEN_BACK);
	//描画モードをバイリニア法にする
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	screen = MakeScreen(SCREEN_X, SCREEN_Y, false);

	//フォントハンドルを初期化する
	for (int i = 0; i < FS_MAX; i++)
	{
		int fontSize[FS_MAX] = { 8, 12, 16, 24, 32, 48, 64, 96 };
		fontHandle[i] = CreateFontToHandle("メイリオ", fontSize[i], -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	}

	while (ProcessMessage() == 0 && ScreenFlip() == 0 && gameEndFlag == false)
	{
		//キーボードの入力状態を更新する
		key.UpdateKeyState();

		//Escapeが押された場合ゲーム終了フラグをtrueにする
		if (key.GetKeyDown(KEY_INPUT_ESCAPE) == true)
		{
			gameEndFlag = true;
		}

		//作成した画像を描画対象にする
		SetDrawScreen(screen);

		//画面をクリアする
		ClearDrawScreen();

		//画面を更新する
		gameState.Update();

		//裏画面に描画する
		SetDrawScreen(DX_SCREEN_BACK);

		DrawExtendGraph(0, 0, screenX, screenY, screen, false);
	}

	DxLib_End();
	return (0);
}
//CSVファイルから行列を指定してその行列のデータを文字列として吐き出す
void LoadCSV(char *string, const char *fileName, int row, int column, int rowMax, int columnMax)
{
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("%sファイル読み込みに失敗しました。\n", fileName);
	}
	char rStr[256] = { 0 };
	int rStrArray = 0;
	for (int i = 0; i <= column + row * columnMax;)
	{
		for (int array = 0; array < 256; array++)rStr[array] = 0;
		while (true)
		{
			char getStr[2] = { 0 };
			fgets(getStr, 2, fp);
			if (getStr[0] == 0)
			{
				return;
			}
			if (getStr[0] == 10)
			{
				i++;
				rStrArray = 0;
				break;
			}
			if (getStr[0] == 44)
			{
				i++;
				rStrArray = 0;
				break;
			}
			rStr[rStrArray] = getStr[0];
			rStrArray++;
		}
	}
	printf("%sファイル(%d,%d)項目 ロード完了 \"%s\"\n", fileName, row, column, rStr);
	sprintf(string, "%s", rStr);
	fclose(fp);
}
//カーソルを描画する
void DrawCursor(int x1, int y1, int x2, int y2, bool up, bool down, bool left, bool right)
{
	static Graphic cursorbace("data/img/gui/cursorBace.png");
	static Graphic arrowNormal("data/img/gui/cursorArrowNormal.png");
	static Graphic arrowBlight("data/img/gui/cursorArrowBlight.png");

	DrawExtendGraph(x1, y1, x2, y2, cursorbace.handle(), true);

	if (up == true && key.GetKey(KEY_INPUT_UP) == true)
	{
		DrawRotaGraph(x1 + (x2 - x1) / 2, y1, 0.6, GetRadian(0), arrowBlight.handle(), true);
	}
	if (up == true && key.GetKey(KEY_INPUT_UP) == false)
	{
		DrawRotaGraph(x1 + (x2 - x1) / 2, y1, 0.4, GetRadian(0), arrowNormal.handle(), true);
	}
	if (down == true && key.GetKey(KEY_INPUT_DOWN) == true)
	{
		DrawRotaGraph(x1 + (x2 - x1) / 2, y2, 0.6, GetRadian(180), arrowBlight.handle(), true);
	}
	if (down == true && key.GetKey(KEY_INPUT_DOWN) == false)
	{
		DrawRotaGraph(x1 + (x2 - x1) / 2, y2, 0.4, GetRadian(180), arrowNormal.handle(), true);
	}
	if (left == true && key.GetKey(KEY_INPUT_LEFT) == true)
	{
		DrawRotaGraph(x1, y1 + (y2 - y1) / 2, 0.6, GetRadian(270), arrowBlight.handle(), true);
	}
	if (left == true && key.GetKey(KEY_INPUT_LEFT) == false)
	{
		DrawRotaGraph(x1, y1 + (y2 - y1) / 2, 0.4, GetRadian(270), arrowNormal.handle(), true);
	}
	if (right == true && key.GetKey(KEY_INPUT_RIGHT) == true)
	{
		DrawRotaGraph(x2, y1 + (y2 - y1) / 2, 0.6, GetRadian(90), arrowBlight.handle(), true);
	}
	if (right == true && key.GetKey(KEY_INPUT_RIGHT) == false)
	{
		DrawRotaGraph(x2, y1 + (y2 - y1) / 2, 0.4, GetRadian(90), arrowNormal.handle(), true);
	}
}
//ロード画面を描画する
void DrawLoad()
{
	static int angle = 0;

	static Graphic loadEye1("data/img/gui/load01.png");
	static Graphic loadEye2("data/img/gui/load02.png");

	//裏画面に描画する
	SetDrawScreen(DX_SCREEN_BACK);

	//画面をクリアする
	ClearDrawScreen();

	//裏画面に描画する
	DrawRotaGraph(screenX - 330, screenY - 30, 0.75, 0, loadEye1.handle(), true);
	DrawRotaGraph(screenX - 330 + cos(GetRadian(angle)) * 10, screenY - 30 + sin(GetRadian(angle)) * 10, 0.75, 0, loadEye2.handle(), true);
	CenterDrawStringToHandle(screenX - 50, screenY, 1, 1.5, "Now loading...", GetColor(127, 255, 255), fontHandle[FS_32]);

	ScreenFlip();

	//目を回す
	angle += 10;
	if (angle == 360)angle = 0;
}
//画面サイズを変更します
void ChangeScreenSize(int x, int y)
{
	screenX = x;
	screenY = y;
	//ウィンドウのサイズを設定する
	SetGraphMode(screenX, screenY, 32);
	//描画モードをバイリニア法にする
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//フォントハンドルを初期化する
	for (int i = 0; i < FS_MAX; i++)
	{
		int fontSize[FS_MAX] = { 8, 12, 16, 24, 32, 48, 64, 96 };
		fontHandle[i] = CreateFontToHandle("メイリオ", fontSize[i], -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	}
	screen = MakeScreen(SCREEN_X, SCREEN_Y, false);
}
//2点間の距離を求める
int CheckDistance(double x1, double y1, double x2, double y2)
{

	double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

	return ((int)distance);

}
//円同士の当たり判定です
bool CheckHitCircleAndCircle(int x1, int y1, double r1, int x2, int y2, double r2)
{
	if (pow(x1 - x2, 2) + pow(y1 - y2, 2) <= pow(r1 + r2, 2))
	{
		return true;
	}

	return false;
}