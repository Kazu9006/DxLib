#include "CObjPlayer.h"

using namespace GameL;

CObjPlayer::CObjPlayer(float pos_x, float pos_y)
{
	m_pos_x = pos_x;
	m_pos_y = pos_y;

	m_vec_x = 0.0f;
	m_vec_y = 0.0f;
	m_move_speed = 1.0f;

	//�ŏ��͐��ʂ�������
	m_posture = PlayerDirection::FRONT;
}

void CObjPlayer::Init()
{

}

void CObjPlayer::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(ObjName::BLOCK);

	if (Input::GetKey(KEY_INPUT_LEFT)) m_vec_x -= m_move_speed;
	if (Input::GetKey(KEY_INPUT_RIGHT)) m_vec_x+= m_move_speed;
	if (Input::GetKey(KEY_INPUT_UP))	m_vec_y-= m_move_speed;
	if (Input::GetKey(KEY_INPUT_DOWN)) m_vec_y+= m_move_speed;

	//���C
	m_vec_x += -(m_vec_x* 0.198f);
	m_vec_y += -(m_vec_y* 0.198f);

	//�u���b�N����ɕK�v��Hit���i�[�p�ϐ�
	bool hit_up, hit_down, hit_left, hit_right;

	//�u���b�N����
	block->BlockHit(&m_pos_x, &m_pos_y, false, &hit_up, &hit_down, &hit_left, &hit_right, &m_vec_x, &m_vec_y, &m_move_speed);

	m_pos_x += m_vec_x;
	m_pos_y += m_vec_y;
}

void CObjPlayer::Draw()
{
	Draw::DrawLRTurn((int)m_pos_x,(int)m_pos_y, ImageSize::ALL, ImageSize::ALL,ImageID::PLAYER,true,0);
}