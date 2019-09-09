#include "SceneObjManager.h"
using namespace GameL;

//�\�[�g�p �`��D�揇�ʂ��r����(�~��)
int DrawOrderCompare(const shared_ptr<CObj> x, const shared_ptr<CObj> y)
{
	return x.get()->GetDrawOrder() < y.get()->GetDrawOrder();
}

list<shared_ptr<CObj>>*	SceneObjManager::m_list_data;	//�Q�[�����s���X�g

//----------------------------CObj----------------------------
CObj::CObj()
{
	m_draw_order = 0;
	m_name = 0;
	m_active = true;
}

//�`��D�揇�ʕύX
void CObj::SetDrawOrder(unsigned int draw_order)
{
	//�l��ύX����
	m_draw_order = draw_order;
	//���X�g����ёւ���
	SceneObjManager::ResetDrawOrder();
}

//�ݒ肵�Ă���`��D�揇�ʎ擾�p
unsigned int CObj::GetDrawOrder()
{
	return m_draw_order;
}

//�I�u�W�F�N�g���OID�ύX�p
void CObj::SetName(int name)
{
	m_name = name;
}

//�I�u�W�F�N�g���OID�擾�p
int CObj::GetName()
{
	return m_name;
}

//�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�ύX
void CObj::SetActive(bool active)
{
	m_active = active;
}

//�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾�p
bool CObj::GetActive()
{
	return m_active;
}
//-----------------------------------------------------------

//----------------------SceneObjManager----------------------
//������
void SceneObjManager::Init()
{
	m_list_data = new list<shared_ptr<CObj>>;
}

//�폜
void SceneObjManager::Delete()
{
	m_list_data->clear();
	delete m_list_data;
}

//�I�u�W�F�N�g�̓o�^
void SceneObjManager::InsertObj(CObj* obj, int name, unsigned int draw_order)
{
	if (obj == nullptr)
		return;

	//�I�u�W�F�N�g�̏��������\�b�h���s
	obj->Init();

	//�I�u�W�F�N�g�̖��O�ݒ�
	obj->SetName(name);

	//�f�[�^�o�^
	unique_ptr<CObj> ptr_obj(obj);
	//�ړ�
	m_list_data->push_front(move(ptr_obj));

	//�I�u�W�F�N�g�̕`��D�揇�ʐݒ�
	obj->SetDrawOrder(draw_order);

	return;
}

//�I�u�W�F�N�g���X�g�폜����
void SceneObjManager::ListDeleteSceneObj()
{
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		m_list_data->erase(itr);
	}
}

//���X�g�ɓo�^���Ă���S�ẴI�u�W�F�N�g�̃A�N�V�������\�b�h���s
void SceneObjManager::ObjsAction()
{
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		//�A�N�e�B�u��ԂȂ�A�N�V�������\�b�h���s
		if ((*itr)->GetActive() == true)
			(*itr)->Action();
	}
}

//���X�g�ɓo�^���Ă���S�ẴI�u�W�F�N�g�̕`�惁�\�b�h���s
void SceneObjManager::ObjsDraw()
{
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		//�A�N�e�B�u��ԂȂ�`�惁�\�b�h���s
		if ((*itr)->GetActive() == true)
			(*itr)->Draw();
	}
}

//�`��D�揇�ʂ�ύX(���X�g��`��D�揇�ʂ̍~���ɕ��ёւ�)
void SceneObjManager::ResetDrawOrder()
{
	//���X�g�ɂQ�ȏ��񂪂���΃\�[�g������
	if (m_list_data->size() >= 2)
	{
		m_list_data->sort(DrawOrderCompare);
	}
}

//���O��񂩂�I�u�W�F�N�g�����P�擾
CObj* SceneObjManager::GetObj(int name)
{
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		//�A�N�e�B�u��ԂȂ�擾�ł���
		if ((*itr)->GetActive() == true)
		{
			//���O����v�����ŏ��̃I�u�W�F�N�g����n��
			if ((*itr)->GetName() == name)
				return (*itr).get();
		}
	}

	return nullptr;
}

//���O��񂩂�I�u�W�F�N�g���𕡐��擾
CObj** SceneObjManager::GetObjs(int name)
{
	CObj** objs = nullptr;

	int obj_count = 0;

	//���O����v����I�u�W�F�N�g���������݂��邩�𐔂���
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		//�A�N�e�B�u��ԂȂ�
		if ((*itr)->GetActive() == true)
		{
			//���O����v�����Ȃ�J�E���g�����Z����
			if ((*itr)->GetName() == name)
				obj_count++;
		}
	}

	//���������̃I�u�W�F�N�g�����邩���������̂Ń��������Z�b�g����
	objs = new CObj*[obj_count];
	//�I�u�W�F�N�g�J�E���g���g���񂵂����̂ŏ�����
	obj_count = 0;

	//��͂�����x�����̃I�u�W�F�N�g���������Ċi�[����
	for (auto itr = m_list_data->begin(); itr != m_list_data->end(); itr++)
	{
		//�A�N�e�B�u��ԂȂ�
		if ((*itr)->GetActive() == true)
		{
			//���O����v����A�i�[����
			if ((*itr)->GetName() == name)
				objs[obj_count++] = (*itr).get();
		}
	}

	//�S�Ă����������̂œn��
	return objs;
}

//-----------------------------------------------------------
