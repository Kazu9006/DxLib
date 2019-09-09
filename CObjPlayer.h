#pragma once
#include "DxLib.h" 
#include "DrawTexture.h"
#include "GameHead.h"
#include "Input.h"
#include "SceneObjManager.h"

using namespace GameL;


//�����̏��
namespace PlayerDirection
{
	constexpr int FRONT	{0};	//����
	constexpr int UP	{1};		//��
	constexpr int DOWN	{2};	//��
	constexpr int LEFT	{3};	//��
	constexpr int RIGHT	{4};//�E
}
//�v���C���[
class CObjPlayer : public CObj{
	public:
		CObjPlayer(float pos_x, float pos_y);//�R���X�g���N�^
		void Init();	//������
		void Action();//����
		void Draw();//�`��
		float GetX() { return m_pos_x; }
		float GetY() { return m_pos_y; }
	private:
		float m_pos_x, m_pos_y;	//�v���C���[�̈ʒu���
		float m_vec_x, m_vec_y;	//�v���C���[�̈ړ��x�N�g��
		float m_move_speed;		//�v���C���[�̈ړ����x
		float m_posture;			//�v���C���[�̌������: PlayerPosture�Q��
};
