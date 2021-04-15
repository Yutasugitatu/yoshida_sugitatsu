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
	TITLETYPE_NONE = 0, //�������Ă��Ȃ����
	TITLETYPE_NORMAL = 1,	//�ʏ���
	TITLETYPE_NORMALLEVEL = 2,
	TITLETYPE_HARDLEVEL = 3,
	TITLETYPE_PRESS = 4,
	TITLETYPE_MOVE = 5,
}TITLETYPE;
typedef enum
{
	TITLESELECT_NORMAL = 0, //�������Ă��Ȃ����
	TITLESELECT_HARD = 1,	//�ʏ���
	TITLESELECT_MAX,
}TITLESELECT;
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p���W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;
}TITLEVERTEX_2D;
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	D3DXVECTOR3 move;
	float rhw;//���W�ϊ��p���W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;
	int nLevel;
}TITLELOGO;
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
TITLESELECT GetSelect(void);
#endif