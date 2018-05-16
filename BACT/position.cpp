#include "position.h"

//コンストラクタ
Position2D::Position2D()
{
	Position2D::xPrivate = 0;
	Position2D::yPrivate = 0;
}
//コンストラクタ(X座標,Y座標)
Position2D::Position2D(int x, int y)
{
	Position2D::xPrivate = x;
	Position2D::yPrivate = y;
}
//デストラクタ
Position2D::~Position2D()
{

}
//Xを取得する
int Position2D::x()
{
	return Position2D::xPrivate;
}
//Yを取得する
int Position2D::y()
{
	return Position2D::yPrivate;
}
//Xに代入する
void Position2D::x(int x)
{
	Position2D::xPrivate = x;
}
//Yに代入する
void Position2D::y(int y)
{
	Position2D::yPrivate = y;
}
//Position2Dに代入する
Position2D& Position2D::operator=(Position2D value)
{
	Position2D::xPrivate = value.xPrivate;
	Position2D::yPrivate = value.yPrivate;
	return (Position2D(Position2D::xPrivate, Position2D::yPrivate));
}
//Position2Dに加算する
Position2D& Position2D::operator+=(Position2D value)
{
	Position2D::xPrivate += value.xPrivate;
	Position2D::yPrivate += value.yPrivate;
	return (Position2D(Position2D::xPrivate, Position2D::yPrivate));
}

//コンストラクタ
Position3D::Position3D()
{
	Position3D::xPrivate = 0;
	Position3D::yPrivate = 0;
	Position3D::zPrivate = 0;
}
//コンストラクタ(X座標,Y座標)
Position3D::Position3D(float x, float y, float z)
{
	Position3D::xPrivate = x;
	Position3D::yPrivate = y;
	Position3D::zPrivate = z;
}
//デストラクタ
Position3D::~Position3D()
{

}
//Xを取得する
float Position3D::x()
{
	return Position3D::xPrivate;
}
//Yを取得する
float Position3D::y()
{
	return Position3D::yPrivate;
}
//Zを取得する
float Position3D::z()
{
	return Position3D::zPrivate;
}
//Xに代入する
void Position3D::x(float x)
{
	Position3D::xPrivate = x;
}
//Yに代入する
void Position3D::y(float y)
{
	Position3D::yPrivate = y;
}
//Zに代入する
void Position3D::z(float z)
{
	Position3D::zPrivate = z;
}
//Position3Dに代入する
Position3D& Position3D::operator=(Position3D value)
{
	Position3D::xPrivate = value.xPrivate;
	Position3D::yPrivate = value.yPrivate;
	Position3D::zPrivate = value.zPrivate;
	return (Position3D(Position3D::xPrivate, Position3D::yPrivate, Position3D::zPrivate));
}
//Position3Dに加算する
Position3D& Position3D::operator+=(Position3D value)
{
	Position3D::xPrivate += value.xPrivate;
	Position3D::yPrivate += value.yPrivate;
	Position3D::zPrivate += value.zPrivate;
	return (Position3D(Position3D::xPrivate, Position3D::yPrivate, Position3D::zPrivate));
}