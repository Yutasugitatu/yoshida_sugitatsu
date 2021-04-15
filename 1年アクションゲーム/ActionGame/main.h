#pragma once
//=============================================================================
//
// DirectX雛型処理 [main.h]
// Author : hoge fuga
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "input.h"
#include "Input.h"
#include "xaudio2.h"
#include "stdio.h"
//=============================================================================
// ライブラリのリンク
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")//システム時刻得とくように必要
#pragma comment(lib,"dinput8.lib")//入力処理に必要

//=============================================================================
// マクロ定義
//=============================================================================
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define NUM_VERTEX (4)//頂点数
#define NUM_POLYGON (2)//ポリゴン数
//=============================================================================
//構造体定義
//=============================================================================
//モードの種類
typedef enum
{
	MODE_TITLE = 0,
	MODE_TITLE2,
	MODE_GAME,
	MODE_RESULT,
	MODE_GOAL,
	MODE_MAX
}MODE;
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用係数
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;
}VERTEX_2D;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);


#endif


