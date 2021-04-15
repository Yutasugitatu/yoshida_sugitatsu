#pragma once
#ifndef _BLOCK_H_
#define _BLOCK_H_
#define _CRT_SECURE_NO_WARNINGS
//#define GROUND_POS_X (300)
//#define GROUND_POS_Y (1000)
#define BLOCK_SIZE_X (50)
#define BLOCK_SIZE_Y (50)
#define BLOCK_SIZE2_X (300)
#define BLOCK_SIZE2_Y (300)
#include "main.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_BLOCK (5000) //�G�̍ő吔
#define MAX_TYPE_BLOCK (128) //�G�̍ő吔

//=============================================================================
//�\���̒�`
//=============================================================================
typedef enum
{
	BLOCKTYPE_NONE = 0, //�������Ă��Ȃ����
	BLOCKTYPE_NORMAL=1,	//�ʏ���
	BLOCKTYPE_DAMAGE=2,
	BLOCKTYPE_JUMP=3,		//�W�����v
	BLOCKTYPE_GOAL=4,
}BLOCKTYPE;
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	D3DXVECTOR3 move;
	BLOCKTYPE type;
	float fWidth;
	float fHeight;
	int nType; //���
	bool bUse; //�g�p���Ă��邩�ǂ���
}BLOCK;
//�G�̏��

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
bool CollisionBlock(D3DXVECTOR3*pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3*pMove, D3DXVECTOR3 Size);
BLOCK*GetBlock(void);

#endif 
