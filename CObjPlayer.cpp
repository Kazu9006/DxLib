#include "CObjPlayer.h"

using namespace GameL;

CObjPlayer::CObjPlayer(float pos_x, float pos_y)
{
	m_pos_x = pos_x;
	m_pos_y = pos_y;

	m_vec_x = 0.0f;
	m_vec_y = 0.0f;
	m_move_speed = 1.0f;

	//最初は正面を向ける
	m_posture = PlayerDirection::FRONT;
}

void CObjPlayer::Init()
{

}

void CObjPlayer::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(ObjName::BLOCK);

	if (Input::GetKey(KEY_INPUT_LEFT)) m_vec_x -= m_move_speed;
	if (Input::GetKey(KEY_INPUT_RIGHT)) m_vec_x+= m_move_speed;
	if (Input::GetKey(KEY_INPUT_UP))	m_vec_y-= m_move_speed;
	if (Input::GetKey(KEY_INPUT_DOWN)) m_vec_y+= m_move_speed;

	//摩擦
	m_vec_x += -(m_vec_x* 0.198f);
	m_vec_y += -(m_vec_y* 0.198f);

	//ブロック判定に必要なHit情報格納用変数
	bool hit_up, hit_down, hit_left, hit_right;

	//ブロック判定
	block->BlockHit(&m_pos_x, &m_pos_y, false, &hit_up, &hit_down, &hit_left, &hit_right, &m_vec_x, &m_vec_y, &m_move_speed);

	m_pos_x += m_vec_x;
	m_pos_y += m_vec_y;
}

void CObjPlayer::Draw()
{
	Draw::DrawLRTurn((int)m_pos_x,(int)m_pos_y, ImageSize::ALL, ImageSize::ALL,ImageID::PLAYER,true,0);
}