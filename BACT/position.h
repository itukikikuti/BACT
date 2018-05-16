#pragma once

class Position2D{
private:
	int xPrivate, yPrivate;							//座標
public:
	Position2D();									//コンストラクタ
	Position2D(int x, int y);						//コンストラクタ(X座標,Y座標)
	~Position2D();									//デストラクタ
	int x();										//Xを取得する
	int y();										//Yを取得する
	void x(int x);									//Xに代入する
	void y(int y);									//Yに代入する
	Position2D& operator=(Position2D value);		//Position2Dに代入する
	Position2D& operator+=(Position2D value);		//Position2Dに加算する
};

class Position3D{
private:
	float xPrivate, yPrivate, zPrivate;				//座標
public:
	Position3D();									//コンストラクタ
	Position3D(float x, float y, float z);			//コンストラクタ(X座標,Y座標,Z座標)
	~Position3D();									//デストラクタ
	float x();										//Xを取得する
	float y();										//Yを取得する
	float z();										//Zを取得する
	void x(float x);								//Xに代入する
	void y(float y);								//Yに代入する
	void z(float z);								//Zに代入する
	Position3D& operator=(Position3D value);		//Position3Dに代入する
	Position3D& operator+=(Position3D value);		//Position3Dに加算する
};