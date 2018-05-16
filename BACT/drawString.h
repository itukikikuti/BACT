#pragma once

extern void CenterDrawString(int x, int y, float centerX, float centerY, const char *string, int color, int edgeColor = 0);							//���W�̒��S�ɕ�����\������
extern void CenterDrawStringToHandle(int x, int y, float centerX, float centerY, const char *string, int color, int fontHandle, int edgeColor = 0);	//���W�̒��S�ɕ�����\������
extern void DrawLineString(int x, int y, const char *string, int color, int edgeColor = 0);															//���������s���ĕ\������
extern void DrawLineStringToHandle(int x, int y, const char *string, int color, int fontHandle, int edgeColor = 0);									//���������s���ĕ\������
extern bool DrawSlowString(int x, int y, const char *string, int speed, int color, int edgeColor = 0, bool reset = false);							//������1�������\������B������\�����I�������true��Ԃ�
extern bool DrawSlowStringToHandle(int x, int y, const char *string, int speed, int color, int fontHandle, int edgeColor = 0, bool reset = false);	//������1�������\������B������\�����I�������true��Ԃ�