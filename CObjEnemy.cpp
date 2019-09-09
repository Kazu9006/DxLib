#include "CObjEnemy.h"

using namespace GameL;

CObjEnemy::CObjEnemy(float x, float y)
{
	m_pos_x = x;
	m_pos_y = y;
}

void CObjEnemy::Init()
{

}

void CObjEnemy::Action()
{

}

void CObjEnemy::Draw()
{
	Draw::Draw((int)m_pos_x, (int)m_pos_y, ImageSize::ALL, ImageSize::ALL, ImageID::ENEMY,true);
}