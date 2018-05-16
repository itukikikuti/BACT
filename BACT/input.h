#pragma once

class Input{
private:
	char KeyStateBuf[256];
	int KeyStateCounter[256];
public:
	Input();						//コンストラクタ
	void UpdateKeyState();			//キーボードの入力状態を更新する
	bool GetAnyKey();				//何か一つでもキーが押されていたらtrueを返す
	bool GetAnyKeyDown();				//何か一つでもキーが押された直後ならtrueを返す
	bool GetKey(int KeyCode);		//特定のキーボードの入力状態を取得する
	bool GetKeyDown(int KeyCode);	//特定のキーボードが押された直後ならtrueを返す
};