#pragma once

enum GameStateType{
	GAME_STATE_LOGO,			//ロゴ
	GAME_STATE_TITLE,			//タイトル
	GAME_STATE_NAME_INPUT,		//名前入力
	GAME_STATE_CHAR_SELECT,		//キャラセレクト
	GAME_STATE_OPENING,			//オープニング
	GAME_STATE_LOAD,			//ロード
	GAME_STATE_SAVE,			//セーブ
	GAME_STATE_OPTION,			//オプション
	GAME_STATE_STAGE_SELECT,	//ステージセレクト
	GAME_STATE_STAGE,			//ステージ
	GAME_STATE_CLEAR,			//クリアー
	GAME_STATE_GAME_OVER,		//ゲームオーバー
	GAME_STATE_ENDING,			//エンディング
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
	void Update();						//画面を更新する
};