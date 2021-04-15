//=============================================================================
//
// DirectX雛型処理 [Polygon.cpp]
// Author :sugi
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "bg2.h"
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBg2 = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg2 = NULL;
int g_nCounterAnimBg2;
int g_nPatternAnimBg2;
float g_fScrollBG2;
//=============================================================================
// 初期化処理
//=============================================================================
void InitBg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_fScrollBG2 = 0.0f;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "bg2.png", &g_pTextureBg2);
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(BG2VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBg2, NULL);
	//頂点情報へのポインタ
	BG2VERTEX_2D *Pvtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	g_pVtxBuffBg2->Lock(0, 0, (void**)&Pvtx, 0);//この書式は変えないこと

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
	g_pVtxBuffBg2->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitBg2(void)
{
	//テクスチャの開放
	if (g_pTextureBg2 != NULL)
	{
		g_pTextureBg2->Release();
		g_pTextureBg2 = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffBg2 != NULL)
	{
		g_pVtxBuffBg2->Release();
		g_pVtxBuffBg2 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBg2(void)
{
	//VERTEX_2D*pVtx;

	//g_fScrollBG += 0.007f;

	////頂点データの範囲をロックし、頂点バッファへのポインタを取得
	//g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);
	//pVtx[0].tex = D3DXVECTOR2(0.0f + g_fScrollBG, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f + g_fScrollBG, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f + g_fScrollBG, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f + g_fScrollBG, 1.0f);
	////アンロック
	//g_pVtxBuffBg->Unlock();

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawBg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBg2, 0, sizeof(BG2VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBg2);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}