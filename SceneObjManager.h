#pragma once
#include <memory>
#include <list>
#include <algorithm>

using namespace std;

namespace GameL
{
	//�p�����ۗp�@�I�u�W�F�N�g�N���X
	class CObj
	{
		public:
			CObj();
			virtual ~CObj() {};
			virtual void Init() = 0;	//�������֐�
			virtual void Action() = 0;	//�����֐�
			virtual void Draw() = 0;	//�`��֐�
			void		 SetDrawOrder(unsigned int draw_order);//�`��D�揇�ʂ�ݒ肷��
			unsigned int GetDrawOrder();					   //�ݒ肵�Ă���`��D�揇�ʎ擾�p
			void		 SetName(int name);					   //�I�u�W�F�N�g���OID�ύX�p
			int			 GetName();							   //�I�u�W�F�N�g���OID�擾�p
			void		 SetActive(bool active);			   //�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�ύX
			bool		 GetActive();						   //�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾�p

		private:
			unsigned int	m_draw_order;	//�`��D�揇��
			int				m_name;			//�I�u�W�F�N�g�̖��OID
			bool			m_active;		//�I�u�W�F�N�g�̃A�N�e�B�u���(Action�EDraw�����s���邩�ǂ���)
	};

	//�I�u�W�F�N�g�}�l�[�W���[
	typedef class SceneObjManager
	{
		public:
			static void Init();					//�������֐�
			static void Delete();				//�폜�֐�
			static void InsertObj(CObj* obj,int name,unsigned int draw_order);	//�I�u�W�F�N�g�̓o�^
			static void ListDeleteSceneObj();	//�I�u�W�F�N�g���X�g�폜����
			static void ObjsAction();			//���X�g�ɓo�^���Ă���S�ẴI�u�W�F�N�g�̃A�N�V�������\�b�h���s
			static void ObjsDraw();				//���X�g�ɓo�^���Ă���S�ẴI�u�W�F�N�g�̕`�惁�\�b�h���s
			static void ResetDrawOrder();		//�`��D�揇�ʂ�ύX(���X�g��`��D�揇�ʂ̍~���ɕ��ёւ�)

			static CObj* GetObj(int name);		//���O��񂩂�I�u�W�F�N�g�����P�擾
			static CObj** GetObjs(int name);	//���O��񂩂�I�u�W�F�N�g���𕡐��擾
		private:
			static list<shared_ptr<CObj>>* m_list_data;	//�Q�[�����s���X�g
	}Objs;

}