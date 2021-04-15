#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_
#define _CRT_SECURE_NO_WARNINGS
#define TITLE_BG (3);
#define MAX_TITLE_LOGO (128)
#define TITLE_SIZE_X (600)
#define TITLE_SIZE_Y (200)
#define MAX_TYPE_TITLE (128)
//include
#include "main.h"
typedef enum
{
	TITLETYPE_NONE = 0, //何もしていない状態
	TITLETYPE_NORMAL = 1,	//通常画面
	TITLETYPE_NORMALLEVEL = 2,
	TITLETYPE_HARDLEVEL = 3,
	TITLETYPE_PRESS = 4,
	TITLETYPE_MOVE = 5,
}TITLETYPE;
typedef enum
{
	TITLESELECT_NORMAL = 0, //何もしていない状態
	TITLESELECT_HARD = 1,	//通常画面
	TITLESELECT_MAX,
}TITLESELECT;
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用紙係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;
}TITLEVERTEX_2D;
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	D3DXVECTOR3 move;
	float rhw;//座標変換用紙係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;
	int nLevel;
}TITLELOGO;
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
TITLESELECT GetSelect(void);
#endif