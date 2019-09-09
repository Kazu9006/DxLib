#include "DrawTexture.h"

using namespace GameL;

TextureHandorList Draw::list;

//�O���O���t�B�b�N�t�@�C����ǂݍ���
void DrawTexture::LoadImage(char* name, int id)
{
	for each (TextureData texure_data in list)
		//�ߋ��ɓo�^�����e�N�X�`���f�[�^�̒��œ���ID�����݂��Ă�����I������
		if (texure_data.image_id == id)
			return;
	
	//�e�N�X�`���f�[�^
	TextureData texture;
	//ID��ݒ�
	texture.image_id = id;
	//�n���h����ݒ�
	texture.texture_handor = new int[1];
	texture.texture_handor[0] = LoadGraph(name);

	//���X�g�ɒǉ�����
	list.push_back(texture);
}
//�O���O���t�B�b�N�t�@�C���̕����ǂݍ���
/*
����1 char* name	:�t�@�C����
����2 int	id		:�o�^ID
����3 int	all_num	:�摜�̕�������
����4 int	x_num	:�摜�̉������ɑ΂��镪����
����5 int	y_num	:�摜�̏c�����ɑ΂��镪����
����6 int	x_size	:�������ꂽ1�̑傫��(X)
����7 int	y_size	:�������ꂽ1�̑傫��(Y)
�������������ꍇ�A�\�����邽�߂ɕK�v�ȕ���ID�͈ȉ��̂悤�Ɋ���U����
	XNum = 4 ; YNum = 4 ; AllNum = 14 ;
	0	1	2	3
	4	5	6	7
	8	9	10	11
	12	13
*/
void DrawTexture::LoadDevImage(char* name, int id, int all_num, int x_num, int y_num, int x_size, int y_size)
{
	for each (TextureData texure_data in list)
		//�ߋ��ɓo�^�����e�N�X�`���f�[�^�̒��œ���ID�����݂��Ă�����I������
		if (texure_data.image_id == id)
			return;

	//�e�N�X�`���f�[�^
	TextureData texture;
	//ID��ݒ肷��
	texture.image_id = id;
	//�n���h����ݒ肷��
	texture.texture_handor = new int[all_num];
	LoadDivGraph(name, all_num, x_num, y_num, x_size, y_size, texture.texture_handor);

	//���X�g�ɒǉ�
	list.push_back(texture);
}

//�o�^�����e�N�X�`����\��
//���� int div_id	:�����ǂݍ��݂������̔ԍ��@�������ǂݍ��݂��Ă��Ȃ��Ȃ�ݒ肵�Ȃ��ł悢
void DrawTexture::Draw(int x,int y,int id, bool trans_flag, int div_id)
{
	for each (TextureData texture_data in list)
	{
		//�w�肳�ꂽID����v������
		if (texture_data.image_id == id)
		{
			//�e�N�X�`�������݂��Ă�����\��
			if (texture_data.texture_handor[div_id] != NULL)
			{
				DrawGraph(x, y, texture_data.texture_handor[div_id], trans_flag);
				return;
			}
		}
	}
}
//�o�^�����e�N�X�`�����T�C�Y�w��ŕ\��
void DrawTexture::Draw(int x, int y, int x_size, int y_size, int id, bool trans_flag, int div_id)
{
	for each (TextureData texture_data in list)
	{
		//�w�肳�ꂽID����v������
		if (texture_data.image_id == id)
		{
			//�e�N�X�`�������݂��Ă�����\��
			if (texture_data.texture_handor[div_id] != NULL)
			{
				DrawExtendGraph(x, y, x + x_size, y + y_size, texture_data.texture_handor[div_id], trans_flag);
			}
		}
	}
}
//�o�^�����e�N�X�`����LR���]���T�C�Y�w��ŕ\��
void DrawTexture::DrawLRTurn(int x, int y, int x_size, int y_size , int id, bool trans_flag, int div_id)
{
	for each (TextureData texture_data in list)
	{
		//�w�肳�ꂽID����v������
		if (texture_data.image_id == id)
		{
			//�e�N�X�`�������݂��Ă�����\��
			if (texture_data.texture_handor[div_id] != NULL)
			{
				DrawExtendGraph(x + x_size, y, x, y+y_size, texture_data.texture_handor[div_id], trans_flag);
			}
		}
	}
}

//�`��p�I�u�W�F�N�g�j��
void DrawTexture::DeleteDrawTexture()
{
	//�ǂ݂��񂾃O���t�B�b�N�f�[�^�����ׂč폜����
	InitGraph();
	//���X�g������������
	list.clear();
}


