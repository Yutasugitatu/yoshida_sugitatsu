#pragma once
#ifndef _RESULT_H_
#define _RESULT_H_
#define _CRT_SECURE_NO_WARNINGS
#define MAX_TYPE_RESULT (128)
//include
#include "main.h"
typedef enum
{
	RESULTSELECT_NONE=0,
	RESULTSELECT_YES = 1, //何もしていない状態
	RESULTSELECT_NO = 2,	//通常画面
	RESULTSELECT_MAX,
}RESULTSELECT;
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用紙係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;
}RESULTVERTEX_2D;

void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
#endif