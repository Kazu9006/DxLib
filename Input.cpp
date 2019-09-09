#include "Input.h"

using namespace GameL;

BYTE2 Input::m_KeyBoard[KEY_MAX];
BYTE2 Input::m_MouseButon[MOUSE_BUTON_MAX];

int Input::m_mouse_x;
int Input::m_mouse_y;

//�������֐�
void Input::Init()
{
	//�L�[�{�[�h�̏�����
	memset(m_KeyBoard, 0x00, sizeof(m_KeyBoard));
	//�}�E�X�̏�����
	memset(m_MouseButon, 0x00, sizeof(m_MouseButon));
	m_mouse_x = m_mouse_y = 0;
}

//�L�[�{�[�h�E�}�E�X�̏�Ԃ��X�V����
void Input::UpDataPushInfo()
{
	//�L�[�{�[�h�̏�Ԃ��X�V����
	for (int key = 0; key < KEY_MAX; key++)
	{
		//�L�[��������Ă�����
		if (CheckHitKey(key))
		{
			//���������Ă�����Ԃ�������
			if ((m_KeyBoard[key] & DownPressing) == DownPressing)
				//�L�[�������Ă��Ȃ���Ԃ��牟�������łȂ��̂Ńt���O��OFF�ɂ���
				m_KeyBoard[key] &= ~DownMoment;
			//���������Ă����ԂłȂ�������
			else//�L�[�������Ă��Ȃ���Ԃ��炨�����Ƃ��Ȃ̂Ńt���O��ON�ɂ���
				m_KeyBoard[key] |= DownMoment;
			

			//�L�[�������Ă���̂Ńt���O��ON�ɂ���
			m_KeyBoard[key] |= DownPressing;
		}
		//�L�[��������Ă��Ȃ�������
		else
		{
			//���������Ă�����Ԃ�������
			if ((m_KeyBoard[key] & DownPressing) == DownPressing)
				//�L�[�����������Ă�����Ԃ��痣�������Ȃ̂Ńt���O��ON�ɂ���
				m_KeyBoard[key] |= UpMoment;
			else//���������Ă��Ȃ���Ԃ�������
				//�L�[�����������Ă��Ȃ���Ԃ��痣�����킯�łȂ��̂Ńt���O��OFF�ɂ���
				m_KeyBoard[key] &= ~UpMoment;

			//�L�[�������Ă��Ȃ��̂Ńt���O��OFF�ɂ���
			m_KeyBoard[key] &= ~DownPressing;
		}
	}

	//�}�E�X�̏�Ԃ��X�V����
	GetMousePoint(&m_mouse_x, &m_mouse_y);
	for (int mouse = 0; mouse < MOUSE_BUTON_MAX; mouse++)
	{
		//GetMouseInput�̖߂�l���ׂ�p
		int reference_mouse;
		switch (mouse)
		{
			//���{�^��
		case 0:
			reference_mouse = MOUSE_INPUT_LEFT;
			break;
			//�E�{�^��
		case 1:
			reference_mouse = MOUSE_INPUT_RIGHT;
			break;
			//�����{�^��
		case 2:
			reference_mouse = MOUSE_INPUT_MIDDLE;
			break;
		}

		//�}�E�X�̃{�^���������ꂽ��
		if (GetMouseInput() == reference_mouse)
		{
			//�}�E�X�����������Ă����ԂȂ�
			if ((m_MouseButon[mouse] & DownPressing) == DownPressing)
				//�}�E�X�������Ă��Ȃ���Ԃ��牟�����킯�ł͂Ȃ��̂Ńt���O��OFF�ɂ���
				m_MouseButon[mouse] &= ~DownMoment;
			//�}�E�X�������Ă��Ȃ���ԂȂ�
			else//�}�E�X�������Ă��Ȃ���Ԃ��牟�����̂Ńt���O��ON�ɂ���
				m_MouseButon[mouse] |= DownMoment;

			//�}�E�X���������̂Ńt���O��ON�ɂ���
			m_MouseButon[mouse] |= DownPressing;
		}
		else
		{
			//�}�E�X�����������Ă�����ԂȂ�
			if ((m_MouseButon[mouse] & DownPressing) == DownPressing)
				//�}�E�X�������Ă����Ԃ��痣�����̂Ńt���O��ON�ɂ���
				m_MouseButon[mouse] |= UpMoment;
			//�}�E�X�𗣂��Ă����ԂȂ�
			else//�}�E�X�������Ă����Ԃ��痣�����킯�łȂ��̂Ńt���O��OFF�ɂ���
				m_MouseButon[mouse] &= ~UpMoment;
			
			//�}�E�X�𗣂����̂Ńt���O��OFF�ɂ���
			m_MouseButon[mouse] &= ~DownPressing;
		}
	}
}

//�L�[�������Ă���Ԃ͏��(�A�ˏ��)
bool Input::GetKey(int key)
{
	if ((m_KeyBoard[key] & DownPressing) == DownPressing)
		return true;
	else
		return false;
}

//�L�[�������Ă��Ȃ���Ԃ��牟������
bool Input::GetKeyDown(int key)
{
	if ((m_KeyBoard[key] & DownMoment) == DownMoment)
		return true;
	else
		return false;
}

//�L�[�������Ă����Ԃ��痣������
bool Input::GetKeyUp(int key)
{
	if ((m_KeyBoard[key] & UpMoment) == UpMoment)
		return true;
	else
		return false;
}

//�}�E�X�������Ă���Ԃ͏��(�A�ˏ��)
//���� int botton:0=���{�^�� 1=�E�{�^�� 2=�����{�^��
bool Input::GetMouseButton(int button)
{
	if ((m_MouseButon[button] & DownPressing) == DownPressing)
		return true;
	else
		return false;
}

//�}�E�X�������Ă��Ȃ���Ԃ��牟������
//���� int botton:0=���{�^�� 1=�E�{�^�� 2=�����{�^��
bool Input::GetMouseButtonDown(int button)
{
	if ((m_MouseButon[button] & DownMoment) == DownMoment)
		return true;
	else
		return false;
}

//�}�E�X�������Ă����Ԃ��痣������
//���� int botton:0=���{�^�� 1=�E�{�^�� 2=�����{�^��
bool Input::GetMouseButtonUp(int button)
{
	if ((m_MouseButon[button] & UpMoment) == UpMoment)
		return true;
	else
		return false;
}


