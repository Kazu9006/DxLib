#pragma once
#include "DxLib.h" 
#include "DrawTexture.h"
#include "GameHead.h"

#include "SceneObjManager.h"

using namespace GameL;

//�G
class CObjEnemy : public CObj{
public:
	CObjEnemy(float x, float y);//�R���X�g���N�^
	void Init();	//������
	void Action();//����
	void Draw();//�`��
	float GetX() { return m_pos_x; }
	float GetY() { return m_pos_y; }
private:
	float m_pos_x, m_pos_y;	//���̈ʒu���
};
