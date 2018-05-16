#include "DxLib.h"
#include "drawString.h"

//���W�̒��S�ɕ�����\������
void CenterDrawString(int x, int y, float centerX, float centerY, const char *string, int color, int edgeColor)
{
	DrawString(x - GetDrawStringWidth(string, strlen(string)) * centerX, y - GetFontSize() * centerY, string, color, edgeColor);
}
//���W�̒��S�ɕ�����\������
void CenterDrawStringToHandle(int x, int y, float centerX, float centerY, const char *string, int color, int fontHandle, int edgeColor)
{
	DrawStringToHandle(x - GetDrawStringWidthToHandle(string, strlen(string), fontHandle) * centerX, y - GetFontSizeToHandle(fontHandle) * centerY, string, color, fontHandle, edgeColor);
}
//���������s���ĕ\������
void DrawLineString(int x, int y, const char *string, int color, int edgeColor)
{
	//�t�H���g�T�C�Y���擾
	int fontSize = GetFontSize();

	//�`�悷�镶�����p�ӂ���
	char tempString[256] = { 0 };
	sprintf_s(tempString, "%s", string);

	int charX = 0;
	int charY = 0;

	//1���������s�R�[�h�����Ȃ���`�悷��
	for (int i = 0; i < 256;)
	{
		//�����񂪏I��������`�揈���𔲂���
		if (tempString[i] == 0)
		{
			break;
		}
		//���s�R�[�h�������當���̕`��ʒu��
		//���s�����ʒu�ɕύX����
		if (tempString[i] == 10)
		{
			charX = 0;
			charY += fontSize * 1.5;
			i += 1;
		}
		//������`�悷��
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

//���������s���ĕ\������
extern void DrawLineStringToHandle(int x, int y, const char *string, int color, int fontHandle, int edgeColor)
{
	//�`�悷�镶�����p�ӂ���
	char tempString[256] = { 0 };
	sprintf_s(tempString, "%s", string);

	int charX = 0;
	int charY = 0;

	//1���������s�R�[�h�����Ȃ���`�悷��
	for (int i = 0; i < 256;)
	{
		//�����񂪏I��������`�揈���𔲂���
		if (tempString[i] == 0)
		{
			break;
		}
		//���s�R�[�h�������當���̕`��ʒu��
		//���s�����ʒu�ɕύX����
		if (tempString[i] == 10)
		{
			charX = 0;
			charY += GetFontSizeToHandle(fontHandle) * 1.5;
			i += 1;
		}
		//������`�悷��
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

//������1�������\������
//������\�����I�������true��Ԃ�
bool DrawSlowString(int x, int y, const char *string, int speed, int color, int edgeColor, bool reset)
{
	//�`�悷�镶�����p�ӂ���
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
//������1�������\������
//������\�����I�������true��Ԃ�
bool DrawSlowStringToHandle(int x, int y, const char *string, int speed, int color, int fontHandle, int edgeColor, bool reset)
{
	//�`�悷�镶�����p�ӂ���
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