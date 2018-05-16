#pragma once

enum GameStateType{
	GAME_STATE_LOGO,			//���S
	GAME_STATE_TITLE,			//�^�C�g��
	GAME_STATE_NAME_INPUT,		//���O����
	GAME_STATE_CHAR_SELECT,		//�L�����Z���N�g
	GAME_STATE_OPENING,			//�I�[�v�j���O
	GAME_STATE_LOAD,			//���[�h
	GAME_STATE_SAVE,			//�Z�[�u
	GAME_STATE_OPTION,			//�I�v�V����
	GAME_STATE_STAGE_SELECT,	//�X�e�[�W�Z���N�g
	GAME_STATE_STAGE,			//�X�e�[�W
	GAME_STATE_CLEAR,			//�N���A�[
	GAME_STATE_GAME_OVER,		//�Q�[���I�[�o�[
	GAME_STATE_ENDING,			//�G���f�B���O
};

class GameState{
private:
	GameStateType state;
public:
	GameState();
	GameState(GameStateType state);
	~GameState();
	GameStateType Get();
	void Change(GameStateType state);
	void Update();						//��ʂ��X�V����
};