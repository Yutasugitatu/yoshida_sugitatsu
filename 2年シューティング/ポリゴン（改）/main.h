//=============================================================================
//
// メイン処理 [main.h]
// Author : 杉立悠太
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "windows.h"
#include "d3dx9.h"
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"
#include "xaudio2.h"
#define _USE_MATH_DEFINES
#include <math.h>
class CRenderer;//前方宣言
class CScene;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int GetFPS(void);


//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment(lib,"dinput8.lib")//入力処理に必要

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH (1280)    // ウインドウの幅
#define SCREEN_HEIGHT (720)    // ウインドウの高さ
#define NUM_VERTEX  4
#define NUM_POLYGON  2
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//#define DIRECTINPUT_VERSION (0x800)				//警告対処用
#define SERVER_PORT_NUM (12345)				//接続先サーバーの接続先ポート
#define LOCAL_IP_ADDRESS	"127.0.0.1"		//ローカルIPアドレス
#define IP_ADDRESS			"52.185.162.69"	//IPアドレス
#define  MAX_SCORE (8)
#define  SCORE_SIZEX (200.0f/10.0f)
#define  SCORE_SIZEY (60.0f)
#define SIZE_HALF (2)
#define IP "13.78.48.186"
//*****************************************************************************
// 構造体定義
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos; // 頂点座標
	float rhw;   // 座標変換用係数(1.0fで固定)
	D3DCOLOR col;  // 頂点カラー
	D3DXVECTOR2 tex; // テクスチャ座標
} VERTEX_2D;

#endif