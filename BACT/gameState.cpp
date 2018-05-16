#include "DxLib.h"
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "graphic.h"
#include "main.h"
#include "gameState.h"
#include "gameStateStage.h"
#include "lifeGame.h"
#include "drawString.h"
#include "stage.h"
#include "player.h"
#include "bullet.h"

using namespace std;

string playerName;
int playerType = 0;
int stageNum = 1;

GameState::GameState()
{
	GameState::state = GAME_STATE_LOGO;
}
GameState::GameState(GameStateType state)
{
	GameState::state = state;
}
GameState::~GameState()
{

}
GameStateType GameState::Get()
{
	return (GameState::state);
}
void GameState::Change(GameStateType state)
{
	GameState::state = state;
	cout << "画面遷移 " << GameState::state << "\n";
}
//画面を更新する
void GameState::Update()
{
	static bool initFlag = false;
	static int titleSoungPosition = 0;
	if (initFlag == false)
	{
		LoadStageData();
		initFlag = true;
	}
	
	switch (GameState::state)
	{
	case GAME_STATE_LOGO:
		if (true)
		{
			static int stateChangeFrame = 200;			//次の画面に遷移するまでのフレーム
			static int drawAlpha = 0;					//画像描画時の透明度
			static Graphic teamLogo("data/img/logo.png");	//ロゴ画像

			//stateChangeFrameが100~81ならdrawAlphaを加算する
			if (stateChangeFrame <= 200 &&
				stateChangeFrame > 180)
			{
				drawAlpha += 12;
			}
			//stateChangeFrameが80~21ならdrawAlphaを255にする
			if (stateChangeFrame <= 180 &&
				stateChangeFrame > 20)
			{
				drawAlpha = 255;
				if (key.GetAnyKey())stateChangeFrame = 20;
			}
			//stateChangeFrameが20~1ならdrawAlphaを減算する
			if (stateChangeFrame <= 20 &&
				stateChangeFrame > 0)
			{
				drawAlpha -= 12;
			}
			//stateChangeFrameが0以下なら
			//この画面で使った変数を初期化して
			//次の画面に遷移する
			if (stateChangeFrame <= 0)
			{
				stateChangeFrame = 100;
				drawAlpha = 0;
				GameState::Change(GAME_STATE_TITLE);
			}

			stateChangeFrame--;	//stateChangeFrameをカウントダウンする

			//チームロゴを描画する
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, drawAlpha);	//透明度を設定
			DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1, 0, teamLogo.handle(), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);		//透明度を戻す
		}
		break;
	case GAME_STATE_TITLE:
		if (true)
		{
			static bool initFlag = false;
			static Graphic titleLogo("data/img/word/BACT.png");
			static Sound title("data/sound/bgm/title.ogg");
			static bool menuFlag = false;

			//初期化
			if (initFlag == false)
			{
				ResetLifeGame(0.5);
				title.Play(DX_PLAYTYPE_LOOP, 255, titleSoungPosition);
				initFlag = true;
			}

			//何かキーが押されたらライフゲームをリセットする
			if (key.GetAnyKey() == true)
			{
				ResetLifeGame(0.01);
			}
			//ライフゲームを描画する
			DrawLifeGame(2, GetColor(0, 31, 63));

			//何かキーが押されたらタイトルメニューに遷移する
			if (menuFlag == false)
			{
				if (key.GetAnyKeyDown() == true)
				{
					title.Volume(127);
					menuFlag = true;
				}
			
				//タイトルロゴを描画する
				DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1.3, 0, titleLogo.handle(), true);

				//ボタンを押してくださいと表示する
				CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 2 + 175, 0.5, 0.5, "ボタンを押してください", GetColor(127, 255, 255), fontHandle[FS_48]);

				//コピーライトを描画する
				CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y, 0.5, 1.5, "(C) 2014-2015 Shirokumago.", GetColor(127, 255, 255), fontHandle[FS_32]);
			}
			else
			{
				static int selectNum = 0;
				static int selectWait = 0;
				
				//上下キーでメニュー選択
				if (key.GetKey(KEY_INPUT_UP) && selectWait == 0)
				{
					if (selectNum == 0)selectNum = 3;
					else selectNum -= 1;
					selectWait = -15;
				}
				if (key.GetKey(KEY_INPUT_DOWN) && selectWait == 0)
				{
					if (selectNum == 3)selectNum = 0;
					else selectNum += 1;
					selectWait = 15;
				}

				if (key.GetKeyDown(KEY_INPUT_Z))
				{
					title.Stop();
					switch (selectNum)
					{
					case 0:
						GameState::Change(GAME_STATE_OPENING);
						break;
					case 1:
						GameState::Change(GAME_STATE_STAGE_SELECT);
						break;
					case 2:
						GameState::Change(GAME_STATE_OPTION);
						break;
					case 3:
						gameEndFlag = true;
						break;
					default:
						GameState::Change(GAME_STATE_OPENING);
					}
					initFlag = false;
				}

				if (key.GetKeyDown(KEY_INPUT_X))
				{
					title.Volume(255);
					menuFlag = false;
				}

				//タイトルロゴを描画する
				SetDrawBright(127, 127, 127);
				DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1.3, 0, titleLogo.handle(), true);
				SetDrawBright(255, 255, 255);

				//操作方法を描画する
				CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) 決定", GetColor(127, 255, 255), fontHandle[FS_32]);
				CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) 戻る", GetColor(127, 255, 255), fontHandle[FS_32]);

				//タイトルのメニューを表示する角度を
				//少し速度に変化をつけて変える
				int y = SCREEN_Y / 2 + 175;
				static int angle = -selectNum * 90;
				int angleAdd[15] = { 1, 1, 1, 2, 3, 3, 6, 9, 13, 20, 30, 5, 2, -1, -5 };

				if (selectWait > 0)
				{
					angle += -angleAdd[15 - selectWait];
					selectWait--;
				}
				if (selectWait < 0)
				{
					angle += angleAdd[15 - -selectWait];
					selectWait++;
				}

				//カーソルを描画する
				DrawCursor(SCREEN_X / 2 - 120, y - 40, SCREEN_X / 2 + 120, y + 40, 1, 1, 0, 0);

				DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", angle);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127 + cos(GetRadian(angle)) * 127);		//透明度を設定
				CenterDrawStringToHandle(SCREEN_X / 2 + 80 - cos(GetRadian(angle)) * 80, y + sin(GetRadian(angle)) * 80, 0.5, 0.5, "初めから", GetColor(127, 255, 255), fontHandle[FS_48]);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127 + cos(GetRadian(angle + 90)) * 127);	//透明度を設定
				CenterDrawStringToHandle(SCREEN_X / 2 + 80 - cos(GetRadian(angle + 90)) * 80, y + sin(GetRadian(angle + 90)) * 80, 0.5, 0.5, "続きから", GetColor(127, 255, 255), fontHandle[FS_48]);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127 + cos(GetRadian(angle + 180)) * 127);	//透明度を設定
				CenterDrawStringToHandle(SCREEN_X / 2 + 80 - cos(GetRadian(angle + 180)) * 80, y + sin(GetRadian(angle + 180)) * 80, 0.5, 0.5, "設定", GetColor(127, 255, 255), fontHandle[FS_48]);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127 + cos(GetRadian(angle + 270)) * 127);	//透明度を設定
				CenterDrawStringToHandle(SCREEN_X / 2 + 80 - cos(GetRadian(angle + 270)) * 80, y + sin(GetRadian(angle + 270)) * 80, 0.5, 0.5, "終了", GetColor(127, 255, 255), fontHandle[FS_48]);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);									//透明度を戻す
			}
		}
		break;
	case GAME_STATE_NAME_INPUT:
		if (true)
		{
			static int nameInputHandle = -1;

			//何かキーが押されたらライフゲームをリセットする
			if (key.GetAnyKey() == true)
			{
				ResetLifeGame(0.01);
			}
			//ライフゲームを描画する
			DrawLifeGame(2, GetColor(0, 31, 63));

			if (nameInputHandle == -1)
			{
				nameInputHandle = MakeKeyInput(15, true, false, false);
				SetActiveKeyInput(nameInputHandle);
				//フォントを大きく滑らかにする
				SetFontSize(48);
				ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);
				//文字の色など
				SetKeyInputStringColor(
					GetColor(63, 191, 255),		//通常の文字
					GetColor(63, 191, 255),		//通常の入力カーソル
					GetColor(63, 191, 255),		//日本語入力時の文字の周り
					GetColor(255, 0, 0),		//日本語入力時の入力カーソル
					GetColor(0, 0, 0),			//日本語入力時の下線
					GetColor(255, 255, 255),	//日本語入力時の変換時の候補の文字
					GetColor(255, 0, 0),		//
					GetColor(0, 0, 0),			//
					GetColor(0, 0, 0),			//
					GetColor(0, 0, 0),			//
					GetColor(0, 63, 127),		//
					GetColor(0, 63, 127),		//
					GetColor(63, 191, 255),		//
					GetColor(0, 0, 0),			//
					GetColor(0, 0, 0),			//
					GetColor(0, 0, 0),			//
					GetColor(0, 0, 0));			//
			}

			switch (CheckKeyInput(nameInputHandle))
			{
			case 0:		//入力中の場合
				if (true)
				{
					//入力した文字を取得する
					char tempPlayerName[256] = { 0 };
					GetKeyInputString(tempPlayerName, nameInputHandle);
					playerName = tempPlayerName;

					//入力した文字を描画する
					DrawKeyInputString(SCREEN_X / 2 - 175, SCREEN_Y / 2, nameInputHandle);

					//操作方法を描画する
					CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 5, 0.5, 0.5, "ナノマシンの名前を決めてください", GetColor(127, 255, 255), fontHandle[FS_48]);
					CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 4, 0.5, 0.5, "キーボードで文字を入力", GetColor(127, 255, 255), fontHandle[FS_32]);
					CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Enter] 決定", GetColor(127, 255, 255), fontHandle[FS_32]);
					CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[Esc] 戻る", GetColor(127, 255, 255), fontHandle[FS_32]);
				}
				break;
			case 1:		//入力完了した場合
				if (true)
				{
					//Zキーが押されたら
					if (key.GetKeyDown(KEY_INPUT_Z))
					{
						//変数を初期化したうえで
						//キャラセレクトに遷移
						DeleteKeyInput(nameInputHandle);
						nameInputHandle = -1;
						//フォントを元に戻す
						SetFontSize(16);
						ChangeFontType(DX_FONTTYPE_NORMAL);
						GameState::Change(GAME_STATE_CHAR_SELECT);
					}

					if (key.GetKeyDown(KEY_INPUT_X))
					{
						DeleteKeyInput(nameInputHandle);
						nameInputHandle = -1;
					}

					//名前が空白だった場合「Nano-001」にする
					if (playerName == "")
					{
						playerName = "Nano-001";
					}

					//確認表示を描画する
					CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 4, 0.5, 1.5, playerName.c_str(), GetColor(127, 255, 255), fontHandle[FS_48]);
					CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 4, 0.5, 0, "でよろしいですか?", GetColor(127, 255, 255), fontHandle[FS_48]);

					//選択肢を表示する
					DrawCursor(SCREEN_X / 2 - 180, SCREEN_Y / 2 - 40, SCREEN_X / 2 + 180, SCREEN_Y / 2 + 40, 0, 0, 0, 0);
					CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 2, 0.5, 0.5, "はい", GetColor(127, 255, 255), fontHandle[FS_96]);

					//操作方法を描画する
					CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) 決定", GetColor(127, 255, 255), fontHandle[FS_32]);
					CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) 戻る", GetColor(127, 255, 255), fontHandle[FS_32]);
				}
				break;
			case 2:		//入力キャンセルした場合
				//ゲーム終了フラグをfalseにしたうえで
				gameEndFlag = false;
				DeleteKeyInput(nameInputHandle);
				nameInputHandle = -1;
				//フォントを元に戻す
				SetFontSize(16);
				ChangeFontType(DX_FONTTYPE_NORMAL);
				//タイトルに遷移する
				GameState::Change(GAME_STATE_TITLE);
				break;
			default:	//エラーが発生した場合
				//もう一度入力を受け付ける
				DeleteKeyInput(nameInputHandle);
				nameInputHandle = -1;
			}
		}
		break;
	case GAME_STATE_CHAR_SELECT:
		if (true)
		{
			static bool csvDataLoadFlag = false;
			static string charName[3];
			static string charCaption[3];
			static string charParameter[3];
			static Graphic berserker("data/img/char/berserkerFront.png");
			static Graphic chaser("data/img/char/chaserFront.png");
			static Graphic assassin("data/img/char/assassinFront.png");
			static bool confirmation = false;

			//csvを読み込んでいなければ読み込む
			if (csvDataLoadFlag == false)
			{
				for (int i = 0; i < 3; i++)
				{
					char tempString[256] = { 0 };
					char tempString2[256] = { 0 };
					LoadCSV(tempString, "data/parameter/charSelect.csv", i + 1, 0, 4, 7);
					charName[i] = tempString;
					LoadCSV(tempString, "data/parameter/charSelect.csv", i + 1, 1, 4, 7);
					sprintf(tempString2, "%s", tempString);
					LoadCSV(tempString, "data/parameter/charSelect.csv", i + 1, 2, 4, 7);
					sprintf(tempString2, "%s\n%s", tempString2, tempString);
					LoadCSV(tempString, "data/parameter/charSelect.csv", i + 1, 3, 4, 7);
					sprintf(tempString2, "%s\n%s", tempString2, tempString);
					charCaption[i] = tempString2;
					LoadCSV(tempString, "data/parameter/charSelect.csv", i + 1, 4, 4, 7);
					sprintf(tempString2, "%s", tempString);
					LoadCSV(tempString, "data/parameter/charSelect.csv", i + 1, 5, 4, 7);
					sprintf(tempString2, "%s\n%s", tempString2, tempString);
					LoadCSV(tempString, "data/parameter/charSelect.csv", i + 1, 6, 4, 7);
					sprintf(tempString2, "%s\n%s", tempString2, tempString);
					charParameter[i] = tempString2;
				}
				csvDataLoadFlag = true;
			}

			//何かキーが押されたらライフゲームをリセットする
			if (key.GetAnyKey() == true)
			{
				ResetLifeGame(0.01);
			}
			//ライフゲームを描画する
			DrawLifeGame(2, GetColor(0, 31, 63));

			if (key.GetKeyDown(KEY_INPUT_LEFT))
			{
				if (playerType == 0)playerType = 2;
				else playerType--;
			}

			if (key.GetKeyDown(KEY_INPUT_RIGHT))
			{
				if (playerType == 2)playerType = 0;
				else playerType++;
			}

			if (key.GetKeyDown(KEY_INPUT_Z))
			{
				if (confirmation == false)confirmation = true;
				else
				{
					GameState::Change(GAME_STATE_STAGE);
				}
			}

			if (key.GetKeyDown(KEY_INPUT_X))
			{
				if (confirmation == true)confirmation = false;
				else
				{
					GameState::Change(GAME_STATE_NAME_INPUT);
				}
			}

			//操作方法を描画する
			CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) 決定", GetColor(127, 255, 255), fontHandle[FS_32]);
			CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) 戻る", GetColor(127, 255, 255), fontHandle[FS_32]);

			//確認画面を描画する
			if (confirmation == true)
			{
				CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 4, 0.5, 1.5, charName[playerType].c_str(), GetColor(127, 255, 255), fontHandle[FS_48]);
				CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 4, 0.5, 0, "でよろしいですか?", GetColor(127, 255, 255), fontHandle[FS_48]);

				//選択肢を表示する
				DrawCursor(SCREEN_X / 2 - 180, SCREEN_Y / 2 - 40, SCREEN_X / 2 + 180, SCREEN_Y / 2 + 40, 0, 0, 0, 0);
				CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 2, 0.5, 0.5, "はい", GetColor(127, 255, 255), fontHandle[FS_96]);

				//操作方法を描画する
				CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) 決定", GetColor(127, 255, 255), fontHandle[FS_32]);
				CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) 戻る", GetColor(127, 255, 255), fontHandle[FS_32]);
			}
			else
			{
				//キャラ説明文を描画する
				DrawStringToHandle(SCREEN_X / 2 + 100, SCREEN_Y / 2 - 200, charName[playerType].c_str(), GetColor(127, 255, 255), fontHandle[FS_48]);
				DrawLineStringToHandle(SCREEN_X / 2 + 100, SCREEN_Y / 2 - 125, charCaption[playerType].c_str(), GetColor(127, 255, 255), fontHandle[FS_32]);
				DrawLineStringToHandle(SCREEN_X / 2 + 100, SCREEN_Y / 2 + 100, charParameter[playerType].c_str(), GetColor(127, 255, 255), fontHandle[FS_32]);

				//キャラを表示する
				DrawCursor(SCREEN_X / 4 - 200, SCREEN_Y / 2 - 350, SCREEN_X / 4 + 200, SCREEN_Y / 2 + 350, 0, 0, 1, 1);
				if (playerType == 0)DrawRotaGraph(SCREEN_X / 4, SCREEN_Y / 2, 1, 0, berserker.handle(), true);
				if (playerType == 1)DrawRotaGraph(SCREEN_X / 4, SCREEN_Y / 2, 1, 0, chaser.handle(), true);
				if (playerType == 2)DrawRotaGraph(SCREEN_X / 4, SCREEN_Y / 2, 1, 0, assassin.handle(), true);
			}
		}
		break;
	case GAME_STATE_OPENING:
		if (true)
		{
			static bool stringInit = false;
			static char openingString[6][256];
			static int stringNum = 0;
			static Graphic backGround("data/img/back/labo.png");
			static int keyWait = 32;
			static int font = CreateFontToHandle("しねきゃぷしょん", 48, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
			static Sound bgm("data/sound/bgm/opening.ogg");

			SetDrawBright(127, 127, 127);
			DrawExtendGraph(0, 0, SCREEN_X, SCREEN_Y, backGround.handle(), true);
			SetDrawBright(255, 255, 255);

			//オープニングのシナリオを読み込む
			if (stringInit == false)
			{
				LoadCSV(openingString[0], "data/parameter/opening.csv", 1, 0, 6, 1);
				LoadCSV(openingString[1], "data/parameter/opening.csv", 2, 0, 6, 1);
				LoadCSV(openingString[2], "data/parameter/opening.csv", 3, 0, 6, 1);
				LoadCSV(openingString[3], "data/parameter/opening.csv", 4, 0, 6, 1);
				LoadCSV(openingString[4], "data/parameter/opening.csv", 5, 0, 6, 1);
				LoadCSV(openingString[5], "data/parameter/opening.csv", 6, 0, 6, 1);

				bgm.Play(DX_PLAYTYPE_LOOP, 192);

				stringInit = true;
			}

			//オープニングのシナリオを進める
			if (key.GetKeyDown(KEY_INPUT_Z))
			{
				if (stringNum < GetArrayLength(openingString) - 1)
				{
					stringNum++;
					keyWait = 32;
				}
				else
				{
					stringNum = 0;
					keyWait = 32;
					GameState::Change(GAME_STATE_NAME_INPUT);
				}
			}

			//オープニングのシナリオを描画する
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - keyWait * 8);
			CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y - 100, 0.5, 0.5, openingString[stringNum], GetColor(127, 255, 255), font);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		
			//操作方法を描画する
			CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) 次へ", GetColor(127, 255, 255), fontHandle[FS_32]);

			if (keyWait > 0)keyWait--;
		}
		break;
	case GAME_STATE_LOAD:
		break;
	case GAME_STATE_SAVE:
		break;
	case GAME_STATE_OPTION:
		if (true)
		{
			static string screenSizeStr[7] = {
				"320x240",
				"640x480",
				"768x576",
				"800x600",
				"1024x768",
				"1280x960",
				"1400x1050",
			};
			static int screenSize = 0;

			//何かキーが押されたらライフゲームをリセットする
			if (key.GetAnyKey() == true)
			{
				ResetLifeGame(0.01);
			}
			//ライフゲームを描画する
			DrawLifeGame(2, GetColor(0, 31, 63));

			//各項目を描画
			DrawStringToHandle(30, 100, "画面サイズ", GetColor(127, 255, 255), fontHandle[FS_32]);

			//各設定項目を描画
			DrawStringToHandle(SCREEN_X / 2, 100, screenSizeStr[screenSize].c_str(), GetColor(127, 255, 255), fontHandle[FS_32]);

			if (key.GetKeyDown(KEY_INPUT_LEFT))
			{
				if (screenSize <= 0)screenSize = 6;
				else screenSize--;
			}

			if (key.GetKeyDown(KEY_INPUT_RIGHT))
			{
				if (screenSize >= 6)screenSize = 0;
				else screenSize++;
			}

			if (key.GetKeyDown(KEY_INPUT_X))
			{
				int screenX[7] = { 320, 640, 768, 800, 1024, 1280, 1400 };
				int screenY[7] = { 240, 480, 576, 600, 768, 960, 1050 };
				ChangeScreenSize(screenX[screenSize], screenY[screenSize]);
				GameState::Change(GAME_STATE_TITLE);
			}

			//操作方法を描画する
			CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) 決定", GetColor(127, 255, 255), fontHandle[FS_32]);
			CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) タイトルへ戻る", GetColor(127, 255, 255), fontHandle[FS_32]);
		}
		break;
	case GAME_STATE_STAGE_SELECT:
		if (true)
		{
			static bool initFlag = false;
			static Graphic stageImage[8];
			static int stageSelectBackImage = 0;
			static int stageImageIndentY[7] = { -250, -250, -100, -100, 50, 50, 380 };

			if (initFlag == false)
			{
				for (int i = 0; i < 7; i++)
				{
					char fileName[256] = { 0 };
					sprintf(fileName, "data/img/gui/stageSelect/stageSelect%d.png", i);
					stageImage[i].Load(fileName);
					initFlag = true;
				}
			}

			if (key.GetKeyDown(KEY_INPUT_Z))
			{
				gameState.Change(GAME_STATE_STAGE);
			}
			if (key.GetKeyDown(KEY_INPUT_X))
			{
				gameState.Change(GAME_STATE_TITLE);
			}
			if (key.GetKeyDown(KEY_INPUT_UP))
			{
				stageNum++;
				if (stageNum > 6){ stageNum = 6; }
			}
			if (key.GetKeyDown(KEY_INPUT_DOWN))
			{
				stageNum--;
				if (stageNum < 0){ stageNum = 0; }
			}

			//何かキーが押されたらライフゲームをリセットする
			if (key.GetAnyKey() == true)
			{
				ResetLifeGame(0.01);
			}
			//ライフゲームを描画する
			DrawLifeGame(2, GetColor(0, 31, 63));

			for (int i = 0; i < 7; i++)
			{
				SetDrawBright(63, 63, 63);
				if (i == stageNum)SetDrawBright(255, 255, 255);
				DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2 + stageImageIndentY[stageNum], 3, 0, stageImage[i].handle(), true);
			}
			SetDrawBright(255, 255, 255);

			DrawCursor(10, SCREEN_Y / 2 - 30, 50 + GetDrawStringWidthToHandle(stage[stageNum].name.c_str(), strlen(stage[stageNum].name.c_str()), fontHandle[FS_32]), SCREEN_Y / 2 + 64, 1, 1, 0, 0);
			DrawStringToHandle(30, SCREEN_Y / 2, stage[stageNum].name.c_str(), GetColor(127, 255, 255), fontHandle[FS_32]);
		
			//操作方法を描画する
			CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) 決定", GetColor(127, 255, 255), fontHandle[FS_32]);
			CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) 戻る", GetColor(127, 255, 255), fontHandle[FS_32]);
		}
		break;
	case GAME_STATE_STAGE:
		GameStateStage(stageNum, playerType);
		break;
	case GAME_STATE_CLEAR:
		//何かキーが押されたらライフゲームをリセットする
		if (key.GetAnyKey() == true)
		{
			ResetLifeGame(0.01);
		}
		//ライフゲームを描画する
		DrawLifeGame(2, GetColor(0, 31, 63));
		break;
	case GAME_STATE_GAME_OVER:
		break;
	case GAME_STATE_ENDING:
		if (true)
		{
			static bool initFlag = false;
			static float y = SCREEN_Y;
			static int endCount = 0;
			static string endingStr;
			static Sound endingBGM("data/sound/bgm/ending.ogg");
			int lineLength = 0;
			ifstream ifs("data/parameter/ending.txt");
			BulletType type = (BulletType)GetRand(BULLET_TYPE_MAX - 1);

			if (initFlag == false)
			{
				if (ifs.fail()){ cout << "ファイル読み込み失敗" << endl; }
				player.Set(SCREEN_X / 2, SCREEN_Y / 4 * 3);
				player.type = 2;
				player.speed = 10;
				LoadBulletData();
				endingBGM.Play(DX_PLAYTYPE_BACK, 255);
				initFlag = true;
			}

			player.holdWeapon = type;
			player.bulletAmmo[type] = 1;

			//弾を更新、描画しています
			//iは警告が出ないよう、unsignedを使って
			//弾を消したら範囲外アクセスが起きないよう
			//continueしています
			for (unsigned int i = 0; i < bullet.size(); i++)
			{
				bullet[i].Move();
				bullet[i].CheckHit();
				if (bullet[i].Delete(i))continue;
				bullet[i].Draw();
			}

			player.Move();
			player.Shoot();
			player.Draw();

			while (getline(ifs, endingStr))
			{
				lineLength++;
				if (y + lineLength * 48 > 0 &&
					y + lineLength * 48 < SCREEN_Y&&
					endingStr != "")
				{
					CenterDrawStringToHandle(SCREEN_X / 2, y + lineLength * 48, 0.5, 0.5, endingStr.c_str(), GetColor(127, 255, 255), fontHandle[FS_32]);
				}
				if (y + lineLength * 48 > SCREEN_Y){ break; }
			}

			if (y > -5720){ y -= 1.2; }
			else{ endCount++; }

			if (endCount>300)
			{
				endingBGM.Stop();
				GameState::Change(GAME_STATE_LOGO);
			}
		}
		break;
	default:
		GameState::Change(GAME_STATE_LOGO);
	}
}