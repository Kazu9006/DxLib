#include "CObjBlock.h"

CObjBlock::CObjBlock()
{
	int map[MAP_SIZE_Y][MAP_SIZE_X] = { { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
										{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
										{ 1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1 },
										{ 1,1,1,0,1,0,1,0,1,1,1,4,1,0,1,0,1 },
										{ 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
										{ 1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1 },
										{ 1,0,0,0,0,0,0,0,1,0,0,3,0,0,0,0,1 },
										{ 1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1 },
										{ 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
										{ 1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1 },
										{ 1,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,1 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	memcpy(m_map, map, sizeof(int) * (MAP_SIZE_X * MAP_SIZE_Y));
}

void CObjBlock::Init()
{

}

void CObjBlock::Action()
{

}

void CObjBlock::Draw()
{
	//�}�b�v�̕\�� (�ŏ��̂P���Player��Enemy���쐬)
	for (int map_y = 0; map_y < MAP_SIZE_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_SIZE_X; map_x++)
		{
			//�摜��ID���i�[�p
			int image_id = -1;
			switch (m_map[map_y][map_x])
			{
					//�u���b�N
				case MapNumber::BLOCK:
					image_id = ImageID::BLOCK;
					break;
					//�v���C���[
				case MapNumber::PLAYER:
				{
					//image_id = ImageID::PLAYER;
					CObjPlayer* player = new CObjPlayer((float)(ImageSize::ALL * map_x), (float)(ImageSize::ALL * map_y));
					Objs::InsertObj(player, ObjName::PLAYER, 10);
					m_map[map_y][map_x] = 0;
					break;
				}
				//�w偂̑�
				case MapNumber::NET:
					image_id = ImageID::NET;
					break;
					//�G
				case MapNumber::ENEMY:
				{
					//image_id = ImageID::ENEMY;
					CObjEnemy* enemy = new CObjEnemy(ImageSize::ALL * map_x, ImageSize::ALL * map_y);
					Objs::InsertObj(enemy, ObjName::ENEMY, 4);
					m_map[map_y][map_x] = 0;
					break;
				}
			}
			//image_id��-1�łȂ���Ή摜��\������
			if (image_id != -1)
				Draw::Draw(map_x * ImageSize::ALL, map_y * ImageSize::ALL, ImageSize::ALL, ImageSize::ALL, image_id, true);
		}
	}
}

//BlockHit�֐�
//�����P	float *x		:������s��object��X�ʒu
//�����Q	float *y		:������s��object��Y�ʒu
//�����R	bool scroll_on	:������s��object�̓X�N���[���̉e����^���邩�ǂ���(true=�^����@false=�^���Ȃ�)
//�����S	bool *up		:�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//�����T	bool *down		:�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//�����U	bool *left		:�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//�����V	bool *right		:�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
//�����W	float *rvx		:���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
//�����X	const float *speed_power	:�X�s�[�h�̃p���[

//������s��object�ƃu���b�N40*40����ŁA�����蔻��Ə㉺���E������s���B
//���̌��ʂ͈����S�`�P�O�ɕԂ�
void CObjBlock::BlockHit(
	float *x, float *y, bool scroll_on,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, const float *speed_power
)
{
	//�Ռ���Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//��l�����������Ă���
	CObjPlayer * player = (CObjPlayer*)Objs::GetObj(ObjName::PLAYER);

	//�����Ă����I�u�W�F�N�g���W����l���̂��̂��ǂ����m�F�p
	bool hero_is_confirmation = false;//true:��l���̂��̂ƒf��  false:��l���̂��̂Ŗ����ƒf��

	//��l���I�u�W�F�N�g�����݂��Ă�����
	if (player != nullptr)
	{
		//X�ʒu������
		if (*x == player->GetX())
		{
			//Y�ʒu������
			if (*y == player->GetY())
			{
				//�����Ă����I�u�W�F�N�g�̍��W����l���̍��W�ƈ�v
				hero_is_confirmation = true;
			}
		}
	}

	//m_mao�̑S�v�f�ɃA�N�Z�X
	for (int map_y = 0; map_y < MAP_SIZE_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_SIZE_X; map_x++)
		{
			//���ׂ悤�Ƃ��Ă�����ꏊ�Ƀu���b�N����������
			if (m_map[map_y][map_x] == 1)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = (float)map_x * ImageSize::ALL;
				float by = (float)map_y * ImageSize::ALL;

				//�X�N���[���̉e��
				float scroll = scroll_on ? 0.0f : 0.0f;

				//�I�u�W�F�N�g�ƃu���b�N�̂����蔻��
				if ((*x + (-scroll) + ImageSize::ALL > bx) && (*x + (-scroll) < bx + ImageSize::ALL) && (*y + ImageSize::ALL > by) && (*y < by + ImageSize::ALL))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;

					//���������߂�
					float len = sqrt(rvx * rvx + rvy * rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					if (len < 88.0)
					{
						//�p�x�ŏ㉺���E�𔻒�
						//�E
						if ((r < 45 && r >= 0) || r > 315)
						{
							if (!(*vx > 0))//�E�Ɉړ����Ă����画�肵�Ȃ�
							{
								*right = true;//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
								*x = bx + ImageSize::ALL + (scroll);//�u���b�N�̈ʒu�@+�@�I�u�W�F�N�g�̕�

																//�^�E(�^��)����
								if ((r < 45 && 0 < r))
								{
									//��l���I�u�W�F�N�g��������K��̃{�^�����������ꍇ���������B
									//��l���I�u�W�F�N�g�ł͂Ȃ������炻�̂܂܏���
									if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetKey(KEY_INPUT_LEFT) == true)))
									{
										//��̏�
										if (r <= 45 && r >= 44)
										{
											//����Y�̈ʒu�̏�̈ʒu�Ɉړ�
											*y = ((float)map_y - 1) * ImageSize::ALL;
											*x += -1.0f;
										}
										else
										{
											*vy = -*speed_power;
										}
									}
								}
								//�^�E(�^��)��艺 && ���Ƀu���b�N������������
								else if (r > 315)
								{
									//��l���I�u�W�F�N�g��������K��̃{�^�����������ꍇ���������B
									//��l���I�u�W�F�N�g�ł͂Ȃ������炻�̂܂܏���
									if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetKey(KEY_INPUT_LEFT) == true)))
									{
										//���̉�
										if (r >= 315 && r <= 316)
										{
											//����Y�̈ʒu�̉��̈ʒu�Ɉړ�
											*y = ((float)map_y + 1) * ImageSize::ALL;
											*x += -1.0f;
										}
										else
										{
											*vy = *speed_power;
										}
									}
								}
								//���ɂ���ɂ��u���b�N����������
								else if (m_map[map_y + 1][map_x] != 0 && m_map[map_y - 1][map_x] != 0)
								{
									*vx = -(*vx) * 0.1f;//-VX*�����W��
								}
							}
						}
						//��
						if (r > 45 && r < 135)
						{
							if (!(*vy < 0))//��Ɉړ����Ă����画�肵�Ȃ�
							{
								*down = true;//�I�u�W�F�N�g�̉��̕������Փ˂��Ă���
								*y = by - ImageSize::ALL;//�u���b�N�̈ʒu�@-�@��l���̕�
								*vy = 0.0f;
								//�^����E
								if (r > 45 && r < 90)
								{
									//�E�̉E
									if (r > 45 && r < 46)
									{
										*x = (map_x + 1) * ImageSize::ALL + scroll;
										*y += 1.0f;
									}
									else
									{
										*vx = *speed_power;
									}
										
								}
								//�^���荶
								else if (r < 135 && r > 90)
								{
									//���̍�
									if (r < 135 && r > 134)
									{
										*x = (map_x - 1) * ImageSize::ALL + scroll;
										*y += 1.0f;
									}
									else
									{
										*vx = -*speed_power;
									}
								}
							}
						}
						//��
						if (r > 135 && r < 225)
						{
							if (!(*vx < 0))//���Ɉړ����Ă����画�肵�Ȃ�
							{
								*left = true;//�I�u�W�F�N�g�̉E�̕������Փ˂��Ă���
								*x = bx - ImageSize::ALL + (scroll);//�u���b�N�̈ʒu�@-�@�I�u�W�F�N�g��

																//�^������
								if ((r > 135 && r < 180))
								{
									//��l���I�u�W�F�N�g��������K��̃{�^�����������ꍇ���������B
									//��l���I�u�W�F�N�g�ł͂Ȃ������炻�̂܂܏���
									if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetKey(KEY_INPUT_RIGHT) == true)))
									{
										//���̍�
										if (r > 135 && r < 136)
										{
											*y = ((float)map_y - 1) * ImageSize::ALL;
											*x += 1.0f;
										}
										else
										{
											*vy = -*speed_power;
										}
											
									}
								}
								//�^����艺
								else if ((r < 225 || r > 180))
								{
									//��l���I�u�W�F�N�g��������K��̃{�^�����������ꍇ���������B
									//��l���I�u�W�F�N�g�ł͂Ȃ������炻�̂܂܏���
									if (hero_is_confirmation == false || (hero_is_confirmation == true && (Input::GetKey(KEY_INPUT_RIGHT) == true)))
									{
										//�E�̉E
										if (r < 225 && r > 224)
										{
											*y = ((float)map_y + 1) * ImageSize::ALL;
											*x += 1.0f;
										}
										else
										{
											*vy = *speed_power;
										}
									}
								}
								//�㉺�Ƀu���b�N����������
								else if (m_map[map_y + 1][map_x] != 0 && m_map[map_y + 1][map_x] != 0)
								{
									*vx = -(*vx) * 0.1f;//-VX*�����W��
								}
							}

						}
						//��
						if (r > 225 && r < 315)
						{
							if (!(*vy > 0))//���Ɉړ����Ă����画�肵�Ȃ�
							{
								*up = true;//��l�����猩�ď�̕������Փ˂��Ă���
								*y = by + ImageSize::ALL;//�u���b�N�̈ʒu�@+�@��l���̕�
								*vy = 0.0f;
								//�^����荶
								if (r > 225 && r < 275)
								{
									//���̍�
									if (r > 225 && r < 226)
									{
										*x = (map_x - 1) * ImageSize::ALL + scroll;
										*y -= 1.0f;
									}
									else
									{
										*vx = -*speed_power;
									}
								}
								//�^�����E
								else if (r < 315 && r > 275)
								{
									//�E�̉E
									if (r < 315 && r > 314)
									{
										*x = (map_x + 1) * ImageSize::ALL + scroll;
										*y -= 1.0f;
									}
									else
									{
										*vx = *speed_power;
									}
										
								}
							}
						}
					}
				}
			}
		}
	}
}
