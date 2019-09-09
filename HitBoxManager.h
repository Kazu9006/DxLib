#pragma once

#include "DxLib.h"
#include <memory>

using namespace std;

namespace GameL
{
	//------�Փˏ�ԍ\����------
	struct HIT_BOX
	{
		float pos_x;	//�ʒuX
		float pos_y;	//�ʒuY
		float width;	//��
		float height;	//����
	};
	//
	struct HIT_STATUS
	{
		int element;			//����
		int name;				//�I�u�W�F�N�g�l�[��
		bool invincible_flag;	//���G�t���O(Hit���薳��)
		int point;				//�|�C���g(�����ȂǂŎg�p����)
	};
	//������������̏��i�[�p
	struct HIT_DATA
	{
		int	element;	//������������̑������
		int name;		//������������̃I�u�W�F�N�g�l�[��
		int point;		//�|�C���g(�����ȂǂŎg�p����)
		float distance;	//����
		float angle;	//�������Ă���p�x
		void* obj;		//�������Ă���I�u�W�F�N�g�A�h���X
	};
	//--------------------------
	//-----�Փ˔���p�N���X-----
	typedef class CHitBox
	{
		friend class CHitBoxManager;
	public:
		CHitBox();
		~CHitBox();
		void SetObj(void* obj);								//����HitBox�����I�u�W�F�N�g��ݒ肷��
		void SetPos(float pos_x, float pos_y,float width , float height);	//�ʒu���E�T�C�Y����ݒ肷��
		void SetPos(float pos_x, float pos_y);				//�ʒu����ݒ肷��
		void SetStatus(int element, int name, int point);	//�����E���O�E�|�C���g����ݒ肷��
		void SetInvincible(bool invincible);				//���G�t���O��ݒ肷��

		int			GetHitCount();							//�������Ă��鑊��̐���Ԃ�
		bool		GetInvincibility();						//���G��Ԃ�Ԃ�
		void*		GetMyObj();								//����Hit_BOX�����I�u�W�F�N�g�A�h���X��Ԃ�
		HIT_STATUS*	GetStatus();							//�X�e�[�^�X�̏�Ԃ�Ԃ�
		HIT_BOX*	GetHitBox();							//�ʒu�E�����E���̏���Ԃ�

		void*	CheckObjNameHit(int obj_name);				//�������Ă��鑊��̒����疼�O�������Ɍ������A�q�b�g�����I�u�W�F�N�g����1�Ԃ�
		void*	CheckObjNameHit(int obj_name, int point);	//�������Ă��鑊��̒����疼�O�E�|�C���g�������Ɍ������A�q�b�g�����I�u�W�F�N�g����1�Ԃ�
		bool	CheckElementHit(int element);				//�������Ă��鑊��̒����瑮���������Ɍ������A�q�b�g�������ǂ�����Ԃ�
		bool	CheckElementHit(int element, int point);	//�������Ă��鑊��̒����瑮���E�|�C���g�������Ɍ������A�q�b�g�������ǂ�����Ԃ�
		
		HIT_DATA** SearchObjNameHit(int obj_name);				//�������Ă��鑊��̒����疼�O�������Ɍ������A�q�b�g�����S��(�ő吔)��HIT_DATA����Ԃ�
		HIT_DATA** SearchObjNameHit(int obj_name, int point);	//�������Ă��鑊��̒����疼�O�E�|�C���g�������Ɍ������A�q�b�g�����S��(�ő吔)��HIT_DATA����Ԃ�
		HIT_DATA** SearchElementHit(int element);				//�������Ă��鑊��̒����瑮���������Ɍ������A�q�b�g�����S��(�ő吔)��HIT_DATA����Ԃ�
		HIT_DATA** searchElementHit(int element, int point);	//�������Ă��鑊��̒����瑮���E�|�C���g�������Ɍ������A�q�b�g�����S��(�ő吔)��HIT_DATA����Ԃ�

		private:
			void SortHitBox();					//�������Ă��鑊��̏��������̏����ŕ��ёւ�
			HIT_STATUS	m_hit_status;			//�����蔻��̏��
			HIT_BOX		m_hit_box;				//�����蔻��̍��W��
			HIT_DATA*	m_hit_data;				//�������Ă��鑊��̏��
			HIT_DATA**	m_hit_search_data;		//�������Ă��鑊��̒��ŒT����̏��
			void*		m_my_obj;				//����HitBox���I�u�W�F�N�g�A�h���X
			int			m_hit_count;			//�q�b�g���Ă���J�E���g��
	}HitBox;
	//--------------------------

	//�Փ˔���}�l�[�W���[
	typedef class CHitBoxManager
	{
		public:
			static void		Init();										//������
			static void		Delete();									//�폜
			static void		SetHitBox(void* obj, float pos_x, float pos_y, float width, float height,int element,int name,int point);//HitBox�̍쐬�E�o�^
			static CHitBox*	GetHitBox(void* obj);						//���g�̃A�h���X������HitBox��Ԃ�
			static void		DeleteHitBox(void* obj);					//���g�̃A�h���X������HitBox�̍폜
			static void		AllHitCheck();								//�Փ˔���
			static void		DeleteAllListData();						//�Փ˔��胊�X�g��j��
			static void		DrawHitBox();								//�f�o�b�N�p�@�����蔻��`��
		private:
			static bool Hit(HIT_BOX* a, HIT_BOX* b, HIT_DATA* hit);		//
			static list<shared_ptr<CHitBox>>* m_list_hitbox;			//�Փ˔��胊�X�g
	}Hits;

}
