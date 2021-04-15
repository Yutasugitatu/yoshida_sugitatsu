#pragma once
//=============================================================================
//
// DirectX雛型処理 [main.h]
// Author : sugi
//
//=============================================================================
#ifndef _CLOUD_H_
#define _CLOUD_H_
#include "main.h"
#define _CRT_SECURE_NO_WARNINGS
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用紙係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;
}CLOUDVERTEX_2D;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitCloud(void);
void UninitCloud(void);
void UpdateCloud(void);
void DrawCloud(void);

#endif
