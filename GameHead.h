#pragma once


//�I�u�W�F�N�g�l�[��------------------------------

//------------------------------------------------


//�����蔻�葮��----------------------------------

//------------------------------------------------


//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^----

//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--


//�ǂݍ��݉摜��ID-------------------------
namespace ImageID
{
	constexpr int NOT	{ 0 };
	constexpr int PLAYER{ 1 };
	constexpr int BLOCK	{ 2 };
	constexpr int NET	{ 3 };
	constexpr int ENEMY	{ 4 };
};
//�摜�̃T�C�Y
namespace ImageSize
{
	constexpr int ALL	{38};
}

//�}�b�v�̔ԍ�
namespace MapNumber
{
	constexpr int NOT	{0};
	constexpr int BLOCK	{1};
	constexpr int PLAYER{2};
	constexpr int NET	{3};
	constexpr int ENEMY	{4};
}

//�I�u�W�F�N�g�l�[��ID
namespace ObjName
{
	constexpr int PLAYER{0};
	constexpr int ENEMY	{1};
	constexpr int BLOCK	{2};
}

//�����蔻�葮��
namespace HitElement
{
	constexpr int NOT{0};//��������(�S�Ă̑����Ɠ����蔻����s��)
	//�ȉ��@���������m�͓����蔻����s��Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�������ݒ蕪�̂�(�ǉ��\)
	constexpr int PLAYER{1};
	constexpr int ENEMY	{2};
	constexpr int ITEM	{3};
	constexpr int MAGIC	{4};
	constexpr int FIELD	{5};
	constexpr int RED	{6};
	constexpr int GREEN	{7};
	constexpr int BLUE	{8};
	constexpr int BLACK	{9};
	constexpr int WHiTE	{10};
}

//�}�N��---------------------------
#define MAP_SIZE_X	(17)
#define MAP_SIZE_Y	(12)
//------------------------------------------------


//�Q�[�����Ŏg�p����N���X�w�b�_------------------

//------------------------------------------------


//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "CObjPlayer.h"
#include "CObjEnemy.h"
#include "CObjBlock.h"

//------------------------------------------------


//�V�[���X�^�[�g�N���X---------------------------

//------------------------------------------------