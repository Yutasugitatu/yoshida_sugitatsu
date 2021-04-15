#pragma once
//=============================================================================
//
// DirectX���^���� [main.h]
// Author : sugi
//
//=============================================================================
#ifndef _CLOUD_H_
#define _CLOUD_H_
#include "main.h"
#define _CRT_SECURE_NO_WARNINGS
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p���W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;
}CLOUDVERTEX_2D;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitCloud(void);
void UninitCloud(void);
void UpdateCloud(void);
void DrawCloud(void);

#endif
