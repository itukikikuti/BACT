#include "DxLib.h"
#include "input.h"

//�R���X�g���N�^
Input::Input()
{
	for (int i = 0; i < 256; i++)
	{
		Input::KeyStateBuf[i] = 0;
	}
}
//�L�[�{�[�h�̓��͏�Ԃ��X�V����
void Input::UpdateKeyState()
{
	GetHitKeyStateAll(Input::KeyStateBuf);

	XINPUT_STATE joyState;
	GetJoypadXInputState(DX_INPUT_PAD1, &joyState);

	if (joyState.Buttons[XINPUT_BUTTON_DPAD_UP])Input::KeyStateBuf[KEY_INPUT_UP] = true;
	if (joyState.Buttons[XINPUT_BUTTON_DPAD_DOWN])Input::KeyStateBuf[KEY_INPUT_DOWN] = true;
	if (joyState.Buttons[XINPUT_BUTTON_DPAD_LEFT])Input::KeyStateBuf[KEY_INPUT_LEFT] = true;
	if (joyState.Buttons[XINPUT_BUTTON_DPAD_RIGHT])Input::KeyStateBuf[KEY_INPUT_RIGHT] = true;
	if (joyState.Buttons[XINPUT_BUTTON_START])Input::KeyStateBuf[KEY_INPUT_RETURN] = true;
	if (joyState.LeftTrigger > 127)Input::KeyStateBuf[KEY_INPUT_LSHIFT] = true;
	if (joyState.RightTrigger > 127)Input::KeyStateBuf[KEY_INPUT_Z] = true;
	if (joyState.Buttons[XINPUT_BUTTON_A])Input::KeyStateBuf[KEY_INPUT_Z] = true;
	if (joyState.Buttons[XINPUT_BUTTON_B])Input::KeyStateBuf[KEY_INPUT_X] = true;
	if (joyState.Buttons[XINPUT_BUTTON_X])Input::KeyStateBuf[KEY_INPUT_X] = true;
	if (joyState.Buttons[XINPUT_BUTTON_Y])Input::KeyStateBuf[KEY_INPUT_LSHIFT] = true;
	if (joyState.ThumbLX < -10000 ||
		joyState.ThumbRX < -10000)
	{
		Input::KeyStateBuf[KEY_INPUT_LEFT] = true;
	}
	if (joyState.ThumbLX > 10000 ||
		joyState.ThumbRX > 10000)
	{
		Input::KeyStateBuf[KEY_INPUT_RIGHT] = true;
	}
	if (joyState.ThumbLY < -10000 ||
		joyState.ThumbRY < -10000)
	{
		Input::KeyStateBuf[KEY_INPUT_DOWN] = true;
	}
	if (joyState.ThumbLY > 10000 ||
		joyState.ThumbRY > 10000)
	{
		Input::KeyStateBuf[KEY_INPUT_UP] = true;
	}

	for (int i = 0; i < 256; i++)
	{
		if (Input::KeyStateBuf[i] == true)Input::KeyStateCounter[i]++;
		else Input::KeyStateCounter[i] = 0;
	}
}
//������ł��L�[��������Ă�����true��Ԃ�
bool Input::GetAnyKey()
{
	for (int i = 0; i < 256; i++)
	{
		if (Input::KeyStateBuf[i] == true)return true;
	}

	return false;
}
//������ł��L�[�������ꂽ����Ȃ�true��Ԃ�
bool Input::GetAnyKeyDown()
{
	for (int i = 0; i < 256; i++)
	{
		if (Input::KeyStateCounter[i] == 1)return true;
	}

	return false;
}
//����̃L�[�{�̓��͏�Ԃ��擾����
bool Input::GetKey(int KeyCode)
{
	return (Input::KeyStateBuf[KeyCode]);
}
//����̃L�[�{�[�h�������ꂽ����Ȃ�true��Ԃ�
bool Input::GetKeyDown(int KeyCode)
{
	if (Input::KeyStateCounter[KeyCode] == 1)
	{
		return true;
	}

	return false;
}