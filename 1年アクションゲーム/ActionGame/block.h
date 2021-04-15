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
// マクロ定義
//=============================================================================
#define MAX_BLOCK (5000) //敵の最大数
#define MAX_TYPE_BLOCK (128) //敵の最大数

//=============================================================================
//構造体定義
//=============================================================================
typedef enum
{
	BLOCKTYPE_NONE = 0, //何もしていない状態
	BLOCKTYPE_NORMAL=1,	//通常画面
	BLOCKTYPE_DAMAGE=2,
	BLOCKTYPE_JUMP=3,		//ジャンプ
	BLOCKTYPE_GOAL=4,
}BLOCKTYPE;
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	D3DXVECTOR3 move;
	BLOCKTYPE type;
	float fWidth;
	float fHeight;
	int nType; //種類
	bool bUse; //使用しているかどうか
}BLOCK;
//敵の状態

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
bool CollisionBlock(D3DXVECTOR3*pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3*pMove, D3DXVECTOR3 Size);
BLOCK*GetBlock(void);

#endif 
