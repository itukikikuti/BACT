/*
2014/12/28
BACT�V�\�[�X�R�[�h
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
	//�R���\�[���Ăяo��
	if (true)AllocConsole(); FILE* fp; freopen_s(&fp, "CONOUT$", "w", stdout); freopen_s(&fp, "CONIN$", "r", stdin);

	//�A�C�R�����Z�b�g����
	SetWindowIconID(IDI_MYICON);

	//���˂���Ղ����t�H���g�����[�h����
	LPCSTR fontPath = "data/font/cinecaption2.28.ttf";
	AddFontResourceEx(fontPath, FR_PRIVATE, NULL);

	//�E�B���h�E�̃^�C�g�����Z�b�g����
	SetMainWindowText("BACT");
	//�E�B���h�E�̃T�C�Y��ݒ肷��
	SetGraphMode(screenX, screenY, 32);
	//�E�B���h�E���[�h�ŋN������
	ChangeWindowMode(true);
	//���O�o�͂��s��Ȃ�
	SetOutApplicationLogValidFlag(false);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)return -1;

	//����ʂɕ`�悷��
	SetDrawScreen(DX_SCREEN_BACK);
	//�`�惂�[�h���o�C���j�A�@�ɂ���
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	screen = MakeScreen(SCREEN_X, SCREEN_Y, false);

	//�t�H���g�n���h��������������
	for (int i = 0; i < FS_MAX; i++)
	{
		int fontSize[FS_MAX] = { 8, 12, 16, 24, 32, 48, 64, 96 };
		fontHandle[i] = CreateFontToHandle("���C���I", fontSize[i], -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	}

	while (ProcessMessage() == 0 && ScreenFlip() == 0 && gameEndFlag == false)
	{
		//�L�[�{�[�h�̓��͏�Ԃ��X�V����
		key.UpdateKeyState();

		//Escape�������ꂽ�ꍇ�Q�[���I���t���O��true�ɂ���
		if (key.GetKeyDown(KEY_INPUT_ESCAPE) == true)
		{
			gameEndFlag = true;
		}

		//�쐬�����摜��`��Ώۂɂ���
		SetDrawScreen(screen);

		//��ʂ��N���A����
		ClearDrawScreen();

		//��ʂ��X�V����
		gameState.Update();

		//����ʂɕ`�悷��
		SetDrawScreen(DX_SCREEN_BACK);

		DrawExtendGraph(0, 0, screenX, screenY, screen, false);
	}

	DxLib_End();
	return (0);
}
//CSV�t�@�C������s����w�肵�Ă��̍s��̃f�[�^�𕶎���Ƃ��ēf���o��
void LoadCSV(char *string, const char *fileName, int row, int column, int rowMax, int columnMax)
{
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("%s�t�@�C���ǂݍ��݂Ɏ��s���܂����B\n", fileName);
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
	printf("%s�t�@�C��(%d,%d)���� ���[�h���� \"%s\"\n", fileName, row, column, rStr);
	sprintf(string, "%s", rStr);
	fclose(fp);
}
//�J�[�\����`�悷��
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
//���[�h��ʂ�`�悷��
void DrawLoad()
{
	static int angle = 0;

	static Graphic loadEye1("data/img/gui/load01.png");
	static Graphic loadEye2("data/img/gui/load02.png");

	//����ʂɕ`�悷��
	SetDrawScreen(DX_SCREEN_BACK);

	//��ʂ��N���A����
	ClearDrawScreen();

	//����ʂɕ`�悷��
	DrawRotaGraph(screenX - 330, screenY - 30, 0.75, 0, loadEye1.handle(), true);
	DrawRotaGraph(screenX - 330 + cos(GetRadian(angle)) * 10, screenY - 30 + sin(GetRadian(angle)) * 10, 0.75, 0, loadEye2.handle(), true);
	CenterDrawStringToHandle(screenX - 50, screenY, 1, 1.5, "Now loading...", GetColor(127, 255, 255), fontHandle[FS_32]);

	ScreenFlip();

	//�ڂ���
	angle += 10;
	if (angle == 360)angle = 0;
}
//��ʃT�C�Y��ύX���܂�
void ChangeScreenSize(int x, int y)
{
	screenX = x;
	screenY = y;
	//�E�B���h�E�̃T�C�Y��ݒ肷��
	SetGraphMode(screenX, screenY, 32);
	//�`�惂�[�h���o�C���j�A�@�ɂ���
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//�t�H���g�n���h��������������
	for (int i = 0; i < FS_MAX; i++)
	{
		int fontSize[FS_MAX] = { 8, 12, 16, 24, 32, 48, 64, 96 };
		fontHandle[i] = CreateFontToHandle("���C���I", fontSize[i], -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	}
	screen = MakeScreen(SCREEN_X, SCREEN_Y, false);
}
//2�_�Ԃ̋��������߂�
int CheckDistance(double x1, double y1, double x2, double y2)
{

	double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

	return ((int)distance);

}
//�~���m�̓����蔻��ł�
bool CheckHitCircleAndCircle(int x1, int y1, double r1, int x2, int y2, double r2)
{
	if (pow(x1 - x2, 2) + pow(y1 - y2, 2) <= pow(r1 + r2, 2))
	{
		return true;
	}

	return false;
}