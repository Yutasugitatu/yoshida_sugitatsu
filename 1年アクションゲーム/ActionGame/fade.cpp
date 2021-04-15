//=============================================================================
//
// DirectX雛型処理 [Polygon.cpp]
// Author :sugi
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "bg.h"
#include "input.h"
#include "title.h"
#include "fade.h"
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;

FADE g_fade;
MODE g_ModeNext = MODE_TITLE;
D3DXCOLOR g_colorFade;
//=============================================================================
// 初期化処理
//=============================================================================
void InitFade(MODE ModeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, "", &g_pTextureFade);
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(BGVERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffFade, NULL);
	//頂点情報へのポインタ
	BGVERTEX_2D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えないこと

											   //頂点座標の設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwでの設定（値は１．０で設定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定（０～２５５の数値を設定)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	////テクスチャ座標の設定（右回りで設定する）
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロックする
	g_pVtxBuffFade->Unlock();
	g_fade = FADE_OUT;
	g_ModeNext = ModeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{

}

FADE GetFade(void)
{
	return g_fade;
}
void SetFade(MODE ModeNext)
{
	g_fade = FADE_OUT;
	g_ModeNext = ModeNext;
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	VERTEX_2D*pVtx;

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_colorFade.a -= FADE_RATE;
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorFade.a += FADE_RATE;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;

				SetMode(g_ModeNext);
			}
		}
	}


	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;
	//アンロック
	g_pVtxBuffFade->Unlock();

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(BGVERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}