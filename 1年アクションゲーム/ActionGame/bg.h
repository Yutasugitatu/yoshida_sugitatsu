#pragma once
//=============================================================================
//
// DirectX雛型処理 [main.h]
// Author : sugi
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#define _CRT_SECURE_NO_WARNINGS
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用紙係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;
}BGVERTEX_2D;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitBg(void);
void UninitBg(void);
void UpdateBg(void);
void DrawBg(void);

#endif
