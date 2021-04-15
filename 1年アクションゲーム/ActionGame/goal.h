#pragma once
#ifndef _GOAL_H_
#define _GOAL_H_
#define _CRT_SECURE_NO_WARNINGS
//include
#include "main.h"
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p���W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;
}GOALVERTEX_2D;

void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
#endif