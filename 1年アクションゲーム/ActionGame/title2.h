#pragma once
//=============================================================================
//
// DirectX���^���� [main.h]
// Author : sugi
//
//=============================================================================
#ifndef _TITLE2_H_
#define _TITLE2_H_
#include "main.h"
#define _CRT_SECURE_NO_WARNINGS
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p���W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;
}TITLE2VERTEX_2D;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitTitle2(void);
void UninitTitle2(void);
void UpdateTitle2(void);
void DrawTitle2(void);

#endif
