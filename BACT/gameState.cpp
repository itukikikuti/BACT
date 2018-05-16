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
	cout << "��ʑJ�� " << GameState::state << "\n";
}
//��ʂ��X�V����
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
			static int stateChangeFrame = 200;			//���̉�ʂɑJ�ڂ���܂ł̃t���[��
			static int drawAlpha = 0;					//�摜�`�掞�̓����x
			static Graphic teamLogo("data/img/logo.png");	//���S�摜

			//stateChangeFrame��100~81�Ȃ�drawAlpha�����Z����
			if (stateChangeFrame <= 200 &&
				stateChangeFrame > 180)
			{
				drawAlpha += 12;
			}
			//stateChangeFrame��80~21�Ȃ�drawAlpha��255�ɂ���
			if (stateChangeFrame <= 180 &&
				stateChangeFrame > 20)
			{
				drawAlpha = 255;
				if (key.GetAnyKey())stateChangeFrame = 20;
			}
			//stateChangeFrame��20~1�Ȃ�drawAlpha�����Z����
			if (stateChangeFrame <= 20 &&
				stateChangeFrame > 0)
			{
				drawAlpha -= 12;
			}
			//stateChangeFrame��0�ȉ��Ȃ�
			//���̉�ʂŎg�����ϐ�������������
			//���̉�ʂɑJ�ڂ���
			if (stateChangeFrame <= 0)
			{
				stateChangeFrame = 100;
				drawAlpha = 0;
				GameState::Change(GAME_STATE_TITLE);
			}

			stateChangeFrame--;	//stateChangeFrame���J�E���g�_�E������

			//�`�[�����S��`�悷��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, drawAlpha);	//�����x��ݒ�
			DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1, 0, teamLogo.handle(), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);		//�����x��߂�
		}
		break;
	case GAME_STATE_TITLE:
		if (true)
		{
			static bool initFlag = false;
			static Graphic titleLogo("data/img/word/BACT.png");
			static Sound title("data/sound/bgm/title.ogg");
			static bool menuFlag = false;

			//������
			if (initFlag == false)
			{
				ResetLifeGame(0.5);
				title.Play(DX_PLAYTYPE_LOOP, 255, titleSoungPosition);
				initFlag = true;
			}

			//�����L�[�������ꂽ�烉�C�t�Q�[�������Z�b�g����
			if (key.GetAnyKey() == true)
			{
				ResetLifeGame(0.01);
			}
			//���C�t�Q�[����`�悷��
			DrawLifeGame(2, GetColor(0, 31, 63));

			//�����L�[�������ꂽ��^�C�g�����j���[�ɑJ�ڂ���
			if (menuFlag == false)
			{
				if (key.GetAnyKeyDown() == true)
				{
					title.Volume(127);
					menuFlag = true;
				}
			
				//�^�C�g�����S��`�悷��
				DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1.3, 0, titleLogo.handle(), true);

				//�{�^���������Ă��������ƕ\������
				CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 2 + 175, 0.5, 0.5, "�{�^���������Ă�������", GetColor(127, 255, 255), fontHandle[FS_48]);

				//�R�s�[���C�g��`�悷��
				CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y, 0.5, 1.5, "(C) 2014-2015 Shirokumago.", GetColor(127, 255, 255), fontHandle[FS_32]);
			}
			else
			{
				static int selectNum = 0;
				static int selectWait = 0;
				
				//�㉺�L�[�Ń��j���[�I��
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

				//�^�C�g�����S��`�悷��
				SetDrawBright(127, 127, 127);
				DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1.3, 0, titleLogo.handle(), true);
				SetDrawBright(255, 255, 255);

				//������@��`�悷��
				CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) ����", GetColor(127, 255, 255), fontHandle[FS_32]);
				CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) �߂�", GetColor(127, 255, 255), fontHandle[FS_32]);

				//�^�C�g���̃��j���[��\������p�x��
				//�������x�ɕω������ĕς���
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

				//�J�[�\����`�悷��
				DrawCursor(SCREEN_X / 2 - 120, y - 40, SCREEN_X / 2 + 120, y + 40, 1, 1, 0, 0);

				DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", angle);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127 + cos(GetRadian(angle)) * 127);		//�����x��ݒ�
				CenterDrawStringToHandle(SCREEN_X / 2 + 80 - cos(GetRadian(angle)) * 80, y + sin(GetRadian(angle)) * 80, 0.5, 0.5, "���߂���", GetColor(127, 255, 255), fontHandle[FS_48]);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127 + cos(GetRadian(angle + 90)) * 127);	//�����x��ݒ�
				CenterDrawStringToHandle(SCREEN_X / 2 + 80 - cos(GetRadian(angle + 90)) * 80, y + sin(GetRadian(angle + 90)) * 80, 0.5, 0.5, "��������", GetColor(127, 255, 255), fontHandle[FS_48]);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127 + cos(GetRadian(angle + 180)) * 127);	//�����x��ݒ�
				CenterDrawStringToHandle(SCREEN_X / 2 + 80 - cos(GetRadian(angle + 180)) * 80, y + sin(GetRadian(angle + 180)) * 80, 0.5, 0.5, "�ݒ�", GetColor(127, 255, 255), fontHandle[FS_48]);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127 + cos(GetRadian(angle + 270)) * 127);	//�����x��ݒ�
				CenterDrawStringToHandle(SCREEN_X / 2 + 80 - cos(GetRadian(angle + 270)) * 80, y + sin(GetRadian(angle + 270)) * 80, 0.5, 0.5, "�I��", GetColor(127, 255, 255), fontHandle[FS_48]);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);									//�����x��߂�
			}
		}
		break;
	case GAME_STATE_NAME_INPUT:
		if (true)
		{
			static int nameInputHandle = -1;

			//�����L�[�������ꂽ�烉�C�t�Q�[�������Z�b�g����
			if (key.GetAnyKey() == true)
			{
				ResetLifeGame(0.01);
			}
			//���C�t�Q�[����`�悷��
			DrawLifeGame(2, GetColor(0, 31, 63));

			if (nameInputHandle == -1)
			{
				nameInputHandle = MakeKeyInput(15, true, false, false);
				SetActiveKeyInput(nameInputHandle);
				//�t�H���g��傫�����炩�ɂ���
				SetFontSize(48);
				ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);
				//�����̐F�Ȃ�
				SetKeyInputStringColor(
					GetColor(63, 191, 255),		//�ʏ�̕���
					GetColor(63, 191, 255),		//�ʏ�̓��̓J�[�\��
					GetColor(63, 191, 255),		//���{����͎��̕����̎���
					GetColor(255, 0, 0),		//���{����͎��̓��̓J�[�\��
					GetColor(0, 0, 0),			//���{����͎��̉���
					GetColor(255, 255, 255),	//���{����͎��̕ϊ����̌��̕���
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
			case 0:		//���͒��̏ꍇ
				if (true)
				{
					//���͂����������擾����
					char tempPlayerName[256] = { 0 };
					GetKeyInputString(tempPlayerName, nameInputHandle);
					playerName = tempPlayerName;

					//���͂���������`�悷��
					DrawKeyInputString(SCREEN_X / 2 - 175, SCREEN_Y / 2, nameInputHandle);

					//������@��`�悷��
					CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 5, 0.5, 0.5, "�i�m�}�V���̖��O�����߂Ă�������", GetColor(127, 255, 255), fontHandle[FS_48]);
					CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 4, 0.5, 0.5, "�L�[�{�[�h�ŕ��������", GetColor(127, 255, 255), fontHandle[FS_32]);
					CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Enter] ����", GetColor(127, 255, 255), fontHandle[FS_32]);
					CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[Esc] �߂�", GetColor(127, 255, 255), fontHandle[FS_32]);
				}
				break;
			case 1:		//���͊��������ꍇ
				if (true)
				{
					//Z�L�[�������ꂽ��
					if (key.GetKeyDown(KEY_INPUT_Z))
					{
						//�ϐ�������������������
						//�L�����Z���N�g�ɑJ��
						DeleteKeyInput(nameInputHandle);
						nameInputHandle = -1;
						//�t�H���g�����ɖ߂�
						SetFontSize(16);
						ChangeFontType(DX_FONTTYPE_NORMAL);
						GameState::Change(GAME_STATE_CHAR_SELECT);
					}

					if (key.GetKeyDown(KEY_INPUT_X))
					{
						DeleteKeyInput(nameInputHandle);
						nameInputHandle = -1;
					}

					//���O���󔒂������ꍇ�uNano-001�v�ɂ���
					if (playerName == "")
					{
						playerName = "Nano-001";
					}

					//�m�F�\����`�悷��
					CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 4, 0.5, 1.5, playerName.c_str(), GetColor(127, 255, 255), fontHandle[FS_48]);
					CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 4, 0.5, 0, "�ł�낵���ł���?", GetColor(127, 255, 255), fontHandle[FS_48]);

					//�I������\������
					DrawCursor(SCREEN_X / 2 - 180, SCREEN_Y / 2 - 40, SCREEN_X / 2 + 180, SCREEN_Y / 2 + 40, 0, 0, 0, 0);
					CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 2, 0.5, 0.5, "�͂�", GetColor(127, 255, 255), fontHandle[FS_96]);

					//������@��`�悷��
					CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) ����", GetColor(127, 255, 255), fontHandle[FS_32]);
					CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) �߂�", GetColor(127, 255, 255), fontHandle[FS_32]);
				}
				break;
			case 2:		//���̓L�����Z�������ꍇ
				//�Q�[���I���t���O��false�ɂ���������
				gameEndFlag = false;
				DeleteKeyInput(nameInputHandle);
				nameInputHandle = -1;
				//�t�H���g�����ɖ߂�
				SetFontSize(16);
				ChangeFontType(DX_FONTTYPE_NORMAL);
				//�^�C�g���ɑJ�ڂ���
				GameState::Change(GAME_STATE_TITLE);
				break;
			default:	//�G���[�����������ꍇ
				//������x���͂��󂯕t����
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

			//csv��ǂݍ���ł��Ȃ���Γǂݍ���
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

			//�����L�[�������ꂽ�烉�C�t�Q�[�������Z�b�g����
			if (key.GetAnyKey() == true)
			{
				ResetLifeGame(0.01);
			}
			//���C�t�Q�[����`�悷��
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

			//������@��`�悷��
			CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) ����", GetColor(127, 255, 255), fontHandle[FS_32]);
			CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) �߂�", GetColor(127, 255, 255), fontHandle[FS_32]);

			//�m�F��ʂ�`�悷��
			if (confirmation == true)
			{
				CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 4, 0.5, 1.5, charName[playerType].c_str(), GetColor(127, 255, 255), fontHandle[FS_48]);
				CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 4, 0.5, 0, "�ł�낵���ł���?", GetColor(127, 255, 255), fontHandle[FS_48]);

				//�I������\������
				DrawCursor(SCREEN_X / 2 - 180, SCREEN_Y / 2 - 40, SCREEN_X / 2 + 180, SCREEN_Y / 2 + 40, 0, 0, 0, 0);
				CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y / 2, 0.5, 0.5, "�͂�", GetColor(127, 255, 255), fontHandle[FS_96]);

				//������@��`�悷��
				CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) ����", GetColor(127, 255, 255), fontHandle[FS_32]);
				CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) �߂�", GetColor(127, 255, 255), fontHandle[FS_32]);
			}
			else
			{
				//�L������������`�悷��
				DrawStringToHandle(SCREEN_X / 2 + 100, SCREEN_Y / 2 - 200, charName[playerType].c_str(), GetColor(127, 255, 255), fontHandle[FS_48]);
				DrawLineStringToHandle(SCREEN_X / 2 + 100, SCREEN_Y / 2 - 125, charCaption[playerType].c_str(), GetColor(127, 255, 255), fontHandle[FS_32]);
				DrawLineStringToHandle(SCREEN_X / 2 + 100, SCREEN_Y / 2 + 100, charParameter[playerType].c_str(), GetColor(127, 255, 255), fontHandle[FS_32]);

				//�L������\������
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
			static int font = CreateFontToHandle("���˂���Ղ����", 48, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
			static Sound bgm("data/sound/bgm/opening.ogg");

			SetDrawBright(127, 127, 127);
			DrawExtendGraph(0, 0, SCREEN_X, SCREEN_Y, backGround.handle(), true);
			SetDrawBright(255, 255, 255);

			//�I�[�v�j���O�̃V�i���I��ǂݍ���
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

			//�I�[�v�j���O�̃V�i���I��i�߂�
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

			//�I�[�v�j���O�̃V�i���I��`�悷��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - keyWait * 8);
			CenterDrawStringToHandle(SCREEN_X / 2, SCREEN_Y - 100, 0.5, 0.5, openingString[stringNum], GetColor(127, 255, 255), font);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		
			//������@��`�悷��
			CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) ����", GetColor(127, 255, 255), fontHandle[FS_32]);

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

			//�����L�[�������ꂽ�烉�C�t�Q�[�������Z�b�g����
			if (key.GetAnyKey() == true)
			{
				ResetLifeGame(0.01);
			}
			//���C�t�Q�[����`�悷��
			DrawLifeGame(2, GetColor(0, 31, 63));

			//�e���ڂ�`��
			DrawStringToHandle(30, 100, "��ʃT�C�Y", GetColor(127, 255, 255), fontHandle[FS_32]);

			//�e�ݒ荀�ڂ�`��
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

			//������@��`�悷��
			CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) ����", GetColor(127, 255, 255), fontHandle[FS_32]);
			CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) �^�C�g���֖߂�", GetColor(127, 255, 255), fontHandle[FS_32]);
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

			//�����L�[�������ꂽ�烉�C�t�Q�[�������Z�b�g����
			if (key.GetAnyKey() == true)
			{
				ResetLifeGame(0.01);
			}
			//���C�t�Q�[����`�悷��
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
		
			//������@��`�悷��
			CenterDrawStringToHandle(0, SCREEN_Y, 0, 1.5, "[Z](A) ����", GetColor(127, 255, 255), fontHandle[FS_32]);
			CenterDrawStringToHandle(SCREEN_X, SCREEN_Y, 1, 1.5, "[X](B) �߂�", GetColor(127, 255, 255), fontHandle[FS_32]);
		}
		break;
	case GAME_STATE_STAGE:
		GameStateStage(stageNum, playerType);
		break;
	case GAME_STATE_CLEAR:
		//�����L�[�������ꂽ�烉�C�t�Q�[�������Z�b�g����
		if (key.GetAnyKey() == true)
		{
			ResetLifeGame(0.01);
		}
		//���C�t�Q�[����`�悷��
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
				if (ifs.fail()){ cout << "�t�@�C���ǂݍ��ݎ��s" << endl; }
				player.Set(SCREEN_X / 2, SCREEN_Y / 4 * 3);
				player.type = 2;
				player.speed = 10;
				LoadBulletData();
				endingBGM.Play(DX_PLAYTYPE_BACK, 255);
				initFlag = true;
			}

			player.holdWeapon = type;
			player.bulletAmmo[type] = 1;

			//�e���X�V�A�`�悵�Ă��܂�
			//i�͌x�����o�Ȃ��悤�Aunsigned���g����
			//�e����������͈͊O�A�N�Z�X���N���Ȃ��悤
			//continue���Ă��܂�
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