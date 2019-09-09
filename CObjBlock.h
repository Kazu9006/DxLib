#pragma once
#include "DxLib.h" 
#include "DrawTexture.h"
#include "GameHead.h"

#include "SceneObjManager.h"

using namespace GameL;

//�}�b�v
class CObjBlock : public CObj {
public:
	CObjBlock();//�R���X�g���N�^
	void Init();	//������
	void Action();//����
	void Draw();//�`��
	//BlockHit�֐�
	void BlockHit(
		float *x, float *y, bool scroll_on,
		bool *up, bool *down, bool *left, bool *right,
		float *vx, float *vy, const float *speed_power
	);
private:
	int m_map[MAP_SIZE_Y][MAP_SIZE_X]; //�}�b�v���
};
