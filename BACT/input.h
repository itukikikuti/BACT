#pragma once

class Input{
private:
	char KeyStateBuf[256];
	int KeyStateCounter[256];
public:
	Input();						//�R���X�g���N�^
	void UpdateKeyState();			//�L�[�{�[�h�̓��͏�Ԃ��X�V����
	bool GetAnyKey();				//������ł��L�[��������Ă�����true��Ԃ�
	bool GetAnyKeyDown();				//������ł��L�[�������ꂽ����Ȃ�true��Ԃ�
	bool GetKey(int KeyCode);		//����̃L�[�{�[�h�̓��͏�Ԃ��擾����
	bool GetKeyDown(int KeyCode);	//����̃L�[�{�[�h�������ꂽ����Ȃ�true��Ԃ�
};