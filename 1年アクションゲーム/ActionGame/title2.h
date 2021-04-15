#pragma once
//=============================================================================
//
// DirectX雛型処理 [main.h]
// Author : sugi
//
//=============================================================================
#ifndef _TITLE2_H_
#define _TITLE2_H_
#include "main.h"
#define _CRT_SECURE_NO_WARNINGS
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用紙係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;
}TITLE2VERTEX_2D;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitTitle2(void);
void UninitTitle2(void);
void UpdateTitle2(void);
void DrawTitle2(void);

#endif
