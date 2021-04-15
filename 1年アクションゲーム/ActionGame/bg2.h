#pragma once
//=============================================================================
//
// DirectX雛型処理 [main.h]
// Author : sugi
//
//=============================================================================
#ifndef _BG2_H_
#define _BG2_H_
#include "main.h"
#define _CRT_SECURE_NO_WARNINGS
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用紙係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;
}BG2VERTEX_2D;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitBg2(void);
void UninitBg2(void);
void UpdateBg2(void);
void DrawBg2(void);

#endif
