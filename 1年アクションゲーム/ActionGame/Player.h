#pragma once
//=============================================================================
//
// DirectX雛型処理 [main.h]
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
//playerの状態
typedef enum
{
	PLAYERSTATE_APPER = 0,	//出現状態
	PLAYERSTATE_NORMAL,	//通常状態
	PLAYERSTATE_DAMAGE,	//ダメージ状態
	PLAYERSTATE_DEATH,	//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;
//構造体定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;	//移動量
	PLAYERSTATE state;	//状態
	bool nJump;
	bool bJump;	//状態カウンタ
	bool scrollR;
	bool scrollL;
	bool scrollUP;
	bool scrollDOWN;
	bool bUse = true;
	bool bLife;
	int nLife;			//ライフ
	int nCounterstate;
	int nDirectionMove;			//表示切替
}PLAYER;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
PLAYER*GetPlayer(void);
#endif

