#pragma once
#include "DxLib.h"

#define KEY_MAX		(256)
#define MOUSE_BUTON_MAX	(3)

//2�o�C�g(�r�b�g���Z�p)
typedef unsigned short  BYTE2;

namespace GameL
{
	class Input
	{
		enum PushInfo
		{
			DownPressing = 0x0001,	//�L�[�������Ă���(�A�ˏ��)
			DownMoment = 0x0010,	//�L�[�������Ă��Ȃ���Ԃ��牟������
			UpMoment = 0x0100,	//�L�[�������Ă����Ԃ��痣������
		};

	public://�֐��p
	//�������֐�
		static void Init();

		//�L�[�{�[�h�E�}�E�X�̏�Ԃ��X�V����
		static void UpDataPushInfo();

		//�L�[�������Ă���Ԃ͏��(�A�ˏ��)
		static bool GetKey(int key);
		//�L�[�������Ă��Ȃ���Ԃ��牟������
		static bool GetKeyDown(int key);
		//�L�[�������Ă����Ԃ��痣������
		static bool GetKeyUp(int key);

		//�}�E�X�������Ă���Ԃ͏��(�A�ˏ��)
		//���� int botton:0=���{�^�� 1=�E�{�^�� 2=�����{�^��
		static bool GetMouseButton(int button);

		//�}�E�X�������Ă��Ȃ���Ԃ��牟������
		//���� int botton:0=���{�^�� 1=�E�{�^�� 2=�����{�^��
		static bool GetMouseButtonDown(int button);

		//�}�E�X�������Ă����Ԃ��痣������
		//���� int botton:0=���{�^�� 1=�E�{�^�� 2=�����{�^��
		static bool GetMouseButtonUp(int button);
	public://�ϐ��p
		static int m_mouse_x, m_mouse_y;//�}�E�X�̍��W
	private://�ϐ��p
		static BYTE2 m_KeyBoard[KEY_MAX];//�L�[�{�[�h�z��
		static BYTE2 m_MouseButon[MOUSE_BUTON_MAX];	//�}�E�X�̃{�^��

	};
}
