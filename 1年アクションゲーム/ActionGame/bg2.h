#pragma once
//=============================================================================
//
// DirectX���^���� [main.h]
// Author : sugi
//
//=============================================================================
#ifndef _BG2_H_
#define _BG2_H_
#include "main.h"
#define _CRT_SECURE_NO_WARNINGS
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p���W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;
}BG2VERTEX_2D;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBg2(void);
void UninitBg2(void);
void UpdateBg2(void);
void DrawBg2(void);

#endif
