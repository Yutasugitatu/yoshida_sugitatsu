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
	RESULTSELECT_YES = 1, //�������Ă��Ȃ����
	RESULTSELECT_NO = 2,	//�ʏ���
	RESULTSELECT_MAX,
}RESULTSELECT;
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p���W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;
}RESULTVERTEX_2D;

void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
#endif