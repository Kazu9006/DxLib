#pragma once
#include "DxLib.h"
#include <list>

using namespace std;

namespace GameL
{
	//�e�N�X�`���f�[�^
	class TextureData
	{
	public:
		int image_id;		//�ǂݍ��ލۂɐݒ肵��ID���(����ID�͑��݂��Ȃ�)
		int* texture_handor;	//�e�N�X�`���̃n���h��
	};

	//�e�N�X�`���n���h�����X�g�p�e���v���[�g
	typedef list<TextureData> TextureHandorList;

	typedef class DrawTexture
	{
		public:
			//�O���O���t�B�b�N�t�@�C����ǂݍ���
			static void LoadImage(char* name, int id);
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
			static void LoadDevImage(char* name, int id, int all_num, int x_num, int y_num, int x_size, int y_size);

			//�o�^�����e�N�X�`����\��
			//����2 int div_id	:�����ǂݍ��݂������̔ԍ��������ǂݍ��݂��Ă��Ȃ��Ȃ�ݒ肵�Ȃ��ł悢
			static void Draw(int x, int y, int id,bool trans_flag, int div_id=0);
			//�o�^�����e�N�X�`�����T�C�Y�w��ŕ\��
			static void Draw(int x, int y, int x_size, int y_size, int id, bool trans_flag, int div_id = 0);
			//�o�^�����e�N�X�`����LR���]���T�C�Y�w��ŕ\��
			static void DrawLRTurn(int x, int y, int x_size, int y_size, int id, bool trans_flag, int div_id = 0);
			//�`��p�I�u�W�F�N�g�j��
			static void DeleteDrawTexture();
		private:
			//�ǂݍ���Texture�ۑ��pList
			static TextureHandorList list;
	}Draw;
}