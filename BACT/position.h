#pragma once

class Position2D{
private:
	int xPrivate, yPrivate;							//���W
public:
	Position2D();									//�R���X�g���N�^
	Position2D(int x, int y);						//�R���X�g���N�^(X���W,Y���W)
	~Position2D();									//�f�X�g���N�^
	int x();										//X���擾����
	int y();										//Y���擾����
	void x(int x);									//X�ɑ������
	void y(int y);									//Y�ɑ������
	Position2D& operator=(Position2D value);		//Position2D�ɑ������
	Position2D& operator+=(Position2D value);		//Position2D�ɉ��Z����
};

class Position3D{
private:
	float xPrivate, yPrivate, zPrivate;				//���W
public:
	Position3D();									//�R���X�g���N�^
	Position3D(float x, float y, float z);			//�R���X�g���N�^(X���W,Y���W,Z���W)
	~Position3D();									//�f�X�g���N�^
	float x();										//X���擾����
	float y();										//Y���擾����
	float z();										//Z���擾����
	void x(float x);								//X�ɑ������
	void y(float y);								//Y�ɑ������
	void z(float z);								//Z�ɑ������
	Position3D& operator=(Position3D value);		//Position3D�ɑ������
	Position3D& operator+=(Position3D value);		//Position3D�ɉ��Z����
};