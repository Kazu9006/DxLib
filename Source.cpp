#include "DxLib.h"
#include <list>
#include <iterator>
#include <iostream>
#include <time.h>

#include "Input.h"
#include "DrawTexture.h"
#include "SceneObjManager.h"
#include "HitBoxManager.h"

#include "GameHead.h"

using namespace std;
using namespace GameL;


//�֐��Q�l�T�C�g
//http://dxlib.o.oo7.jp/dxfunc.html

//�}�b�v�̍쐻
void MapCreate(int map[][MAP_SIZE_X]);
//Map����`��
void DrawMap(int map[][MAP_SIZE_X]);
//�ړ������֐�
void Move(int &playerX, int &playerY,int &ballX,int &ballY, int map[][MAP_SIZE_X]);
//�֐������_��
//�����P	int min	:�ŏ���
//�����Q	int max	:�ő吔
//�߂�l	�ŏ�������ő吔�̊ԂŃ����_���ɒl��n��
int GetRandom(int min, int max);
//�Q�[���I������
bool EndOfGameDetermination(int ballX, int ballY, int map[][MAP_SIZE_X]);

//�v���u������WinMain����n�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);	//Window���[�h(�E�B���h�E���[�h)

	if (DxLib_Init() == -1)	//DX���C�u��������������
		return -1;			//�G���[����������I��

	//�摜�f�[�^�̓ǂݍ���
	Draw::LoadDevImage	("Image/Player.png"	, ImageID::PLAYER,10,3,4,40,40);
	//Draw::LoadImage		("Image/Player.png", ImageID::PLAYER);
	Draw::LoadImage		("Image/Block.png"	, ImageID::BLOCK);
	Draw::LoadImage		("Image/Net.png"	, ImageID::NET);
	Draw::LoadDevImage	("Image/Enemy.png"	, ImageID::ENEMY,3,3,1,40,40);

	//�`�����o�b�N�o�b�t�@�ɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);
	
	//�C���v�b�g������
	Input::Init();
	//�I�u�W�F�N�g�}�l�[�W���[�������u
	SceneObjManager::Init();
	//�����蔻�菉����
	CHitBoxManager::Init();

	//�}�b�v�I�u�W�F�N�g����
	CObjBlock* block = new CObjBlock();
	Objs::InsertObj(block,ObjName::BLOCK,5);

	//�Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		//�L�[�̏�Ԃ��X�V����
		Input::UpDataPushInfo();

		//�e�L�X�g��\��
		DrawString(0, 0, "Text", 0xffff);

		//(��)�@�S�Ă̓o�^�ς݃I�u�W�F�N�g�̃A�N�V���������s
		SceneObjManager::ObjsAction();


		//�Q�[�����I���������ǂ���������s��
		if (false)
		{
			DrawString(255, 255, "�Q�[���N���A�I�I�I�I�I�I�I", 0xfffff);
			DrawString(260, 300, "Esc�������ƃQ�[���I������B", 0xffff);
		}

		//(��)�S�Ă̓o�^�ς݂̃I�u�W�F�N�g�̕`������s
		SceneObjManager::ObjsDraw();

		//�G�X�P�[�v�L�[���͂ŏI������
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		ScreenFlip();//��ʂ̃t���b�v
		//�o�b�N�o�b�t�@����������
		ClearDrawScreen();
		
	}

	//�I�u�W�F�N�g�}�l�[�W���[��j��
	SceneObjManager::Delete();
	//�`��p�I�u�W�F�N�g��j��
	Draw::DeleteDrawTexture();
	//�����蔻���j��
	CHitBoxManager::Delete();

	DxLib_End();	//DX���C�u�����g�p�̏I������

	return 0;	//�\�t�g�̏I��

}
//�w�肳�ꂽID�̈ʒu����pos_x�Epos_y�Ɋi�[����
//����������ꍇ�́A�ŏ��Ɍ������ꏊ���i�[����
void GetTheSpecifiedIDPos(int id,int map[][MAP_SIZE_X],int &pos_x,int &pos_y)
{
	for (int map_y = 0; map_y < MAP_SIZE_Y; map_y++)
	{
		for (int map_x = 0; map_x < MAP_SIZE_X; map_x++)
		{
			if (map[map_y][map_x] == id)
			{
				pos_x = map_x; pos_y = map_y;
				return;
			}
		}
	}
	pos_x = -1; pos_y = -1;
	return;
}
//�w�肳�ꂽ�ꏊ��ID�����擾
int GetTheSpecifiedPos(int pos_x, int pos_y, int map[][MAP_SIZE_X])
{
	return map[pos_y][pos_x];
}
//�ړ������֐�
void Move(int &playerX,int &playerY, int &ballX, int &ballY,int map[][MAP_SIZE_X])
{
	//�ړ��x�N�g��
	int playerVX=0, playerVY=0;

	//�L�[�{�[�h����
	if (Input::GetKeyDown(KEY_INPUT_LEFT)) playerVX--;
	if (Input::GetKeyDown(KEY_INPUT_RIGHT)) playerVX++;
	if (Input::GetKeyDown(KEY_INPUT_UP)) playerVY--;
	if (Input::GetKeyDown(KEY_INPUT_DOWN)) playerVY++;

	//�ړ��������ꏊ���ړ��\�ꏊ�Ȃ�
	if (GetTheSpecifiedPos(playerX + playerVX, playerY + playerVY, map) == 0)
	{
		//Player�̈ړ���ɋʂ����݂��Ă�����
		if (playerX + playerVX == ballX && playerY + playerVY == ballY)
		{
			//�ʂ��ړ��������ꏊ���ړ��\�ȏꏊ�Ȃ�Player��Ball���ړ�������
			if (GetTheSpecifiedPos(ballX + playerVX, ballY + playerVY, map) == 0 ||
				GetTheSpecifiedPos(ballX + playerVX, ballY + playerVY, map) == 3)
			{
				playerX += playerVX;
				playerY += playerVY;
				ballX	+= playerVX;
				ballY	+= playerVY;
			}
		}
		//Player�̈ړ���ɋʂ��Ȃ���Έړ�������
		else
		{
			playerX += playerVX;
			playerY += playerVY;
		}

	}
}
//�֐������_��
//�����P	int min	:�ŏ���
//�����Q	int max	:�ő吔
//�߂�l	�ŏ�������ő吔�̊ԂŃ����_���ɒl��n��
int GetRandom(int min, int max)
{
	static char s = 0;
	if (s == 0)
	{
		srand((unsigned)time(NULL));
		s = 1;
	}
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}
//�Q�[���I������
bool EndOfGameDetermination(int ballX, int ballY, int map[][MAP_SIZE_X])
{
	//�{�[���̈ʒu�Ɍ�������΃Q�[���I��
	if (GetTheSpecifiedPos(ballX, ballY, map) == 3)
	{
		return true;
	}

	return false;
}