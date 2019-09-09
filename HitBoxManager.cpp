#include "DrawTexture.h"	//�f�o�b�NHitBox�\���p
#include "HitBoxManager.h"

using namespace GameL;

//�|�C���^�����S�ɍ폜������
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = nullptr;}}

//�����蔻��̕��������������
#define MAX_HITS	(10)



//-------------------CHitBox-------------------
CHitBox::CHitBox()
{
	m_my_obj = nullptr;
	m_hit_data = new HIT_DATA[MAX_HITS];
	m_hit_search_data = new HIT_DATA*[MAX_HITS];
	m_hit_count = 0;
	memset(&m_hit_status, 0x00, sizeof(HIT_STATUS));
}
CHitBox::~CHitBox()
{
	SAFE_DELETE_ARRAY(m_hit_data);
	SAFE_DELETE_ARRAY(m_hit_search_data);
}
//����HitBox�����I�u�W�F�N�g��ݒ肷��
void CHitBox::SetObj(void* obj)
{
	m_my_obj;
}
//�ʒu���E�T�C�Y����ݒ肷��
void CHitBox::SetPos(float pos_x, float pos_y, float width,float height )
{
	m_hit_box.pos_x = pos_x;
	m_hit_box.pos_y = pos_y;
	m_hit_box.width = width;
	m_hit_box.height = height;
	
}
//�ʒu����ݒ肷��
void CHitBox::SetPos(float pos_x, float pos_y)
{
	m_hit_box.pos_x = pos_x;
	m_hit_box.pos_y = pos_y;
}
//�����E���O�E�|�C���g����ݒ肷��
void CHitBox::SetStatus(int element, int name, int point)
{
	m_hit_status.element = element;
	m_hit_status.name = name;
	m_hit_status.point = point;
}
//���G�t���O��ݒ肷��
void CHitBox::SetInvincible(bool invincible)
{
	m_hit_status.invincible_flag = invincible;
}
//�������Ă��鑊��̐���Ԃ�
int	CHitBox::GetHitCount()
{
	return m_hit_count;
}
//���G��Ԃ�Ԃ�
bool CHitBox::GetInvincibility()
{
	return m_hit_status.invincible_flag;
}
//����HIT_BOX�����I�u�W�F�N�g�A�h���X��Ԃ�
void* CHitBox::GetMyObj()
{
	return m_my_obj;
}
//�X�e�[�^�X�̏�Ԃ�Ԃ�
HIT_STATUS*	CHitBox::GetStatus()
{
	return &m_hit_status;
}
//�ʒu�E�����E���̏���Ԃ�
HIT_BOX* CHitBox::GetHitBox()
{
	return &m_hit_box;
}


//�������Ă��鑊��̒����疼�O�������Ɍ������A�q�b�g�����I�u�W�F�N�g����1�Ԃ�
void* CHitBox::CheckObjNameHit(int obj_name)
{
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].name == obj_name)
				return m_hit_data[hit_count].obj;
	return nullptr;
}
//�������Ă��鑊��̒����疼�O�E�|�C���g�������Ɍ������A�q�b�g�����I�u�W�F�N�g����1�Ԃ�
void* CHitBox::CheckObjNameHit(int obj_name, int point)
{
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].name == obj_name)
				if(m_hit_data[hit_count].point == point)
				return m_hit_data[hit_count].obj;
	return nullptr;
}
//�������Ă��鑊��̒����瑮���������Ɍ������A�q�b�g�������ǂ�����Ԃ�
bool CHitBox::CheckElementHit(int element)
{
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].element == element)
				return true;
	return false;
}
//�������Ă��鑊��̒����瑮���E�|�C���g�������Ɍ������A�q�b�g�������ǂ�����Ԃ�
bool CHitBox::CheckElementHit(int element, int point)
{
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].element == element)
				if(m_hit_data[hit_count].point == point)
					return true;
	return false;
}

//�������Ă��鑊��̒����疼�O�������Ɍ������A�q�b�g�����S��(�ő吔)��HIT_DATA����Ԃ�
HIT_DATA** CHitBox::SearchObjNameHit(int obj_name)
{
	//�������Ă��鑊��̏��������̏����ɕ��ёւ�
	SortHitBox();
	//�T��������̂ŏ��i�[�p�ϐ��̃��������Z�b�g����
	memset(&(*m_hit_search_data), 0x00, sizeof(HIT_DATA*)*MAX_HITS);
	//�T���Ńq�b�g������
	int search_count = 0;
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].name == obj_name)
				m_hit_search_data[search_count++] = &m_hit_data[hit_count];
			
	//�T���q�b�g���Ȃ�������nullptr��Ԃ�
	if (search_count == 0)
		return nullptr;
	else
		return m_hit_search_data;
}
//�������Ă��鑊��̒����疼�O�E�|�C���g�������Ɍ������A�q�b�g�����S��(�ő吔)��HIT_DATA����Ԃ�
HIT_DATA** CHitBox::SearchObjNameHit(int obj_name, int point)
{
	//�������Ă��鑊��̏��������̏����ɕ��ёւ�
	SortHitBox();
	//�T��������̂ŏ��i�[�p�ϐ��̃��������Z�b�g����
	memset(&(*m_hit_search_data), 0x00, sizeof(HIT_DATA*)*MAX_HITS);
	//�T���Ńq�b�g������
	int search_count = 0;
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].name == obj_name)
				if(m_hit_data[hit_count].point == point)
					m_hit_search_data[search_count++] = &m_hit_data[hit_count];

	//�T���q�b�g���Ȃ�������nullptr��Ԃ�
	if (search_count == 0)
		return nullptr;
	else
		return m_hit_search_data;
}
//�������Ă��鑊��̒����瑮���������Ɍ������A�q�b�g�����S��(�ő吔)��HIT_DATA����Ԃ�
HIT_DATA** CHitBox::SearchElementHit(int element)
{
	//�������Ă��鑊��̏��������̏����ɕ��ёւ�
	SortHitBox();
	//�T��������̂ŏ��i�[�p�ϐ��̃��������Z�b�g����
	memset(&(*m_hit_search_data), 0x00, sizeof(HIT_DATA*)*MAX_HITS);
	//�T���Ńq�b�g������
	int search_count = 0;
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].element == element)
				m_hit_search_data[search_count++] = &m_hit_data[hit_count];

	//�T���q�b�g���Ȃ�������nullptr��Ԃ�
	if (search_count == 0)
		return nullptr;
	else
		return m_hit_search_data;
}
//�������Ă��鑊��̒����瑮���E�|�C���g�������Ɍ������A�q�b�g�����S��(�ő吔)��HIT_DATA����Ԃ�
HIT_DATA** CHitBox::searchElementHit(int element, int point)
{
	//�������Ă��鑊��̏��������̏����ɕ��ёւ�
	SortHitBox();
	//�T��������̂ŏ��i�[�p�ϐ��̃��������Z�b�g����
	memset(&(*m_hit_search_data), 0x00, sizeof(HIT_DATA*)*MAX_HITS);
	//�T���Ńq�b�g������
	int search_count = 0;
	for (int hit_count = 0; hit_count < m_hit_count; hit_count++)
		if (m_hit_data[hit_count].obj != nullptr)
			if (m_hit_data[hit_count].element == element)
				if(m_hit_data[hit_count].point == point)
					m_hit_search_data[search_count++] = &m_hit_data[hit_count];

	//�T���q�b�g���Ȃ�������nullptr��Ԃ�
	if (search_count == 0)
		return nullptr;
	else
		return m_hit_search_data;
}

//�������Ă��鑊��̏��������̏����ŕ��ёւ�
void CHitBox::SortHitBox()
{
	for (int front = 0; front < m_hit_count; front++)	//�O
	{
		for (int rear = front + 1; rear < m_hit_count; rear++)	//��
		{
			//�O�̋������擾
			float front_distance = (m_hit_data[front].obj == nullptr) ? 9999.0f : m_hit_data[front].distance;
			//��̋������擾
			float rear_distance =  (m_hit_data[rear].obj == nullptr)  ? 9999.0f : m_hit_data[rear].distance;

			//�O�̋�������̋������Z����Ε��ёւ����s��
			if (front_distance > rear_distance)
			{
				HIT_DATA hit_data;
				hit_data = m_hit_data[front];
				m_hit_data[front] = m_hit_data[rear];
				m_hit_data[rear] = hit_data;
			}
		}
	}
}
//---------------------------------------------

//---------------CHitBoxManager----------------
//������
void CHitBoxManager::Init()
{
	m_list_hitbox = new list<shared_ptr<CHitBox>>;
}
//�폜
void CHitBoxManager::Delete()
{
	DeleteAllListData();
	delete m_list_hitbox;
}
//HitBox�̍쐬�E�o�^
void CHitBoxManager::SetHitBox(void* obj, float pos_x, float pos_y, float width, float height, int element, int name, int point)
{
	//�f�[�^�̍쐬
	shared_ptr<CHitBox> ptr_box(new CHitBox());
	ptr_box->SetPos(pos_x,pos_y,width,height);	//�ʒu�E���E������ݒ肷��
	ptr_box->SetStatus(element,name,point);		//�����E���O�E�|�C���g��ݒ肷��
	ptr_box->SetObj(obj);						//�I�u�W�F�N�g����ݒ肷��
	ptr_box->SetInvincible(false);				//���G����ݒ肷��
	m_list_hitbox->push_front(ptr_box);			//�f�[�^�̓o�^
}
//���g�̃A�h���X������HitBox��Ԃ�
CHitBox* CHitBoxManager::GetHitBox(void* obj)
{
	for each (auto itr in *m_list_hitbox)
	{
		if (itr->GetMyObj() == obj)
			return itr.get();
	}
}
//���g�̃A�h���X������HitBox�̍폜
void	CHitBoxManager::DeleteHitBox(void* obj)
{
	/*for each (auto itr in *m_list_hitbox)
	{
		if (itr->GetMyObj() == obj)
		{
			m_list_hitbox->erase(itr.get());
			return;
		}
	}*/
	for (auto itr = m_list_hitbox->begin(); itr != m_list_hitbox->end(); itr++)
	{
		if ((*itr).get()->GetMyObj() == obj)
		{
			m_list_hitbox->erase(itr);	//�f�[�^�폜
			return;
		}
	}

}
//�Փ˔���
void	CHitBoxManager::AllHitCheck()
{
	for each (auto itr_my in *m_list_hitbox)
	{

	}
}
//�Փ˔��胊�X�g��j��
void	CHitBoxManager::DeleteAllListData()
{
	m_list_hitbox->clear();
}
//�f�o�b�N�p�@�����蔻��`��
void	CHitBoxManager::DrawHitBox()
{

}
//---------------------------------------------