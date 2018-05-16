#include "position.h"

//�R���X�g���N�^
Position2D::Position2D()
{
	Position2D::xPrivate = 0;
	Position2D::yPrivate = 0;
}
//�R���X�g���N�^(X���W,Y���W)
Position2D::Position2D(int x, int y)
{
	Position2D::xPrivate = x;
	Position2D::yPrivate = y;
}
//�f�X�g���N�^
Position2D::~Position2D()
{

}
//X���擾����
int Position2D::x()
{
	return Position2D::xPrivate;
}
//Y���擾����
int Position2D::y()
{
	return Position2D::yPrivate;
}
//X�ɑ������
void Position2D::x(int x)
{
	Position2D::xPrivate = x;
}
//Y�ɑ������
void Position2D::y(int y)
{
	Position2D::yPrivate = y;
}
//Position2D�ɑ������
Position2D& Position2D::operator=(Position2D value)
{
	Position2D::xPrivate = value.xPrivate;
	Position2D::yPrivate = value.yPrivate;
	return (Position2D(Position2D::xPrivate, Position2D::yPrivate));
}
//Position2D�ɉ��Z����
Position2D& Position2D::operator+=(Position2D value)
{
	Position2D::xPrivate += value.xPrivate;
	Position2D::yPrivate += value.yPrivate;
	return (Position2D(Position2D::xPrivate, Position2D::yPrivate));
}

//�R���X�g���N�^
Position3D::Position3D()
{
	Position3D::xPrivate = 0;
	Position3D::yPrivate = 0;
	Position3D::zPrivate = 0;
}
//�R���X�g���N�^(X���W,Y���W)
Position3D::Position3D(float x, float y, float z)
{
	Position3D::xPrivate = x;
	Position3D::yPrivate = y;
	Position3D::zPrivate = z;
}
//�f�X�g���N�^
Position3D::~Position3D()
{

}
//X���擾����
float Position3D::x()
{
	return Position3D::xPrivate;
}
//Y���擾����
float Position3D::y()
{
	return Position3D::yPrivate;
}
//Z���擾����
float Position3D::z()
{
	return Position3D::zPrivate;
}
//X�ɑ������
void Position3D::x(float x)
{
	Position3D::xPrivate = x;
}
//Y�ɑ������
void Position3D::y(float y)
{
	Position3D::yPrivate = y;
}
//Z�ɑ������
void Position3D::z(float z)
{
	Position3D::zPrivate = z;
}
//Position3D�ɑ������
Position3D& Position3D::operator=(Position3D value)
{
	Position3D::xPrivate = value.xPrivate;
	Position3D::yPrivate = value.yPrivate;
	Position3D::zPrivate = value.zPrivate;
	return (Position3D(Position3D::xPrivate, Position3D::yPrivate, Position3D::zPrivate));
}
//Position3D�ɉ��Z����
Position3D& Position3D::operator+=(Position3D value)
{
	Position3D::xPrivate += value.xPrivate;
	Position3D::yPrivate += value.yPrivate;
	Position3D::zPrivate += value.zPrivate;
	return (Position3D(Position3D::xPrivate, Position3D::yPrivate, Position3D::zPrivate));
}