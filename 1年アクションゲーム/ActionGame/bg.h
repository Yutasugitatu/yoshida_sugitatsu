#pragma once
//=============================================================================
//
// DirectX���^���� [main.h]
// Author : sugi
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#define _CRT_SECURE_NO_WARNINGS
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p���W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;
}BGVERTEX_2D;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBg(void);
void UninitBg(void);
void UpdateBg(void);
void DrawBg(void);

#endif
