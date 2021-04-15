#include "main.h"
#include "Input.h"
#include "Player.h"
#include "game.h"
#include "Bg.h"
#include "title.h"
#include "result.h"
#include "Bg2.h"
#include "Cloud.h"
#include "block.h"
#include "map.h"
#include "fade.h"
#include "common.h"
#include "sound.h"
#include "goal.h"
#include "title2.h"
#define COUNT_WAIT_FINISH_GAME (60)
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
//=============================================================================
// ����������
//=============================================================================
void InitGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_gamestate = GAMESTATE_NORMAL;

	g_nCounterGameState = 0;
	InitTitle2();
	InitResult();
	InitGoal();
	InitPlayer();
	InitBg();
	InitBg2();
	InitCloud();
	InitBlock();
	InitMap();
	//���̏���������
	
}
void UninitGame(void)
{
	UninitPlayer();
	UninitBg();
	UninitBlock();
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	switch (g_gamestate)
	{
	case GAMESTATE_NORMAL:
		//PlaySound(SOUND_LABEL_BGM001);
		UpdateBg();
		UpdateBg2();
		UpdateCloud();
		UpdatePlayer();
		UpdateBlock();
		break;
	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= COUNT_WAIT_FINISH_GAME &&GetFade()==FADE_NONE)
		{
			g_nCounterGameState = 0;
			//��ʃ��[�h�̐ݒ�
			SetFade(MODE_RESULT);
			//g_gamestate = GAMESTATE_NONE;
		}
		break;
	case GAMESTATE_CLEAR:
		g_nCounterGameState++;
		if (g_nCounterGameState >= COUNT_WAIT_FINISH_GAME &&GetFade() == FADE_NONE)
		{
			g_nCounterGameState = 0;
			//��ʃ��[�h�̐ݒ�
			SetFade(MODE_GOAL);
		}
		break;
	}

}
void DrawGame(void)
{
	//�h���[�|���S���̕`��
	DrawBg();
	DrawBg2();
	DrawCloud();
	DrawPlayer();
	DrawBlock();
}
//=============================================================================
// �Q�[����Ԃ̐ݒ�
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	g_nCounterGameState = 0;
}
//=============================================================================
// �Q�[����Ԃ̎擾
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gamestate;
}