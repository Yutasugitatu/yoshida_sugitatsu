#pragma once
#ifndef _GOAL_H_
#define _GOAL_H_
#define _CRT_SECURE_NO_WARNINGS
//include
#include "main.h"
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用紙係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;
}GOALVERTEX_2D;

void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
#endif