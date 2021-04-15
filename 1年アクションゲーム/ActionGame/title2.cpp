//=============================================================================
//
// DirectX雛型処理 [Polygon.cpp]
// Author :sugi
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "fade.h"
#include "title2.h"
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle2 = NULL;
//=============================================================================
// 初期化処理
//=============================================================================
void InitTitle2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Description.png", &g_pTextureTitle2);
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(TITLE2VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle2, NULL);
	//頂点情報へのポインタ
	TITLE2VERTEX_2D *Pvtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	g_pVtxBuffTitle2->Lock(0, 0, (void**)&Pvtx, 0);//この書式は変えないこと

											   //頂点座標の設定（右回りで設定する）
	Pvtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Pvtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	Pvtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	Pvtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwでの設定（値は１．０で設定)
	Pvtx[0].rhw = 1.0f;
	Pvtx[1].rhw = 1.0f;
	Pvtx[2].rhw = 1.0f;
	Pvtx[3].rhw = 1.0f;

	//頂点カラーの設定（０～２５５の数値を設定)
	Pvtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	Pvtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	Pvtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	Pvtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定（右回りで設定する）
	Pvtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Pvtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Pvtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Pvtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロックする
	g_pVtxBuffTitle2->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle2(void)
{
	//テクスチャの開放
	if (g_pTextureTitle2 != NULL)
	{
		g_pTextureTitle2->Release();
		g_pTextureTitle2 = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffTitle2 != NULL)
	{
		g_pVtxBuffTitle2->Release();
		g_pVtxBuffTitle2 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle2(void)
{
	FADE pFade;
	pFade = GetFade();
	if (GetKeyBoardTrigger(DIK_RETURN) && pFade == FADE_NONE)
	{
		SetFade(MODE_GAME);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTitle2, 0, sizeof(TITLE2VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle2);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}