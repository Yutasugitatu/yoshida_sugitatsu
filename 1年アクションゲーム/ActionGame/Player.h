#pragma once
//=============================================================================
//
// DirectX���^���� [main.h]
// Author : sugi
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#define _CRT_SECURE_NO_WARNINGS
#define PLAYER_POS_X (300)
#define PLAYER_POS_Y (600)
#define PLAYER_SIZE_X (100)
#define PLAYER_SIZE_Y (100)
#define MAX_TYPE_PLAYER (128)
//player�̏��
typedef enum
{
	PLAYERSTATE_APPER = 0,	//�o�����
	PLAYERSTATE_NORMAL,	//�ʏ���
	PLAYERSTATE_DAMAGE,	//�_���[�W���
	PLAYERSTATE_DEATH,	//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;
//�\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;	//�ړ���
	PLAYERSTATE state;	//���
	bool nJump;
	bool bJump;	//��ԃJ�E���^
	bool scrollR;
	bool scrollL;
	bool scrollUP;
	bool scrollDOWN;
	bool bUse = true;
	bool bLife;
	int nLife;			//���C�t
	int nCounterstate;
	int nDirectionMove;			//�\���ؑ�
}PLAYER;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
PLAYER*GetPlayer(void);
#endif

