#pragma once
#include "MyPG.h"
#include "sound.h"


extern  void  MyGameMain_Finalize();
extern  void  MyGameMain_Initialize();
extern  void  MyGameMain_UpDate();
extern  void  MyGameMain_Render2D();
//extern int savex;
//extern int savey;
enum class TaskFlag
{
	Non,		//�^�X�N�����I�����
	Title,		//�^�C�g��
	Game,		//�Q�[���{��
	Ending,
	NewGame,
	//�ȉ��K�v�ɉ����Ēǉ�
};