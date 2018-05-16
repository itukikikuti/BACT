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

//CSV�t�@�C������s����w�肵�Ă��̍s��̃f�[�^�𕶎���Ƃ��ēf���o��
extern void LoadCSV(char *string, const char *fileName, int row, int column, int rowMax, int columnMax);
//�J�[�\����`�悷��
extern void DrawCursor(int x1, int y1, int x2, int y2, bool up, bool down, bool left, bool right);
//���[�h��ʂ�`�悷��
extern void DrawLoad();
//��ʃT�C�Y��ύX���܂�
extern void ChangeScreenSize(int x, int y);
//2�_�Ԃ̋��������߂�
extern int CheckDistance(double x1, double y1, double x2, double y2);
//�~���m�̓����蔻��ł�
extern bool CheckHitCircleAndCircle(int x1, int y1, double r1, int x2, int y2, double r2);