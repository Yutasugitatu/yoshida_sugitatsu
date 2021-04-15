//=============================================================================
//
// DirectX雛型処理 [Polygon.cpp]
// Author :sugi
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "bg.h"
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBg = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;
int g_nCounterAnimBg;
int g_nPatternAnimBg;
float g_fScrollBG;
//=============================================================================
// 初期化処理
//=============================================================================
void InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_fScrollBG = 0.0f;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "bg.png", &g_pTextureBg);
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(BGVERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBg, NULL);
	//頂点情報へのポインタ
	BGVERTEX_2D *Pvtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	g_pVtxBuffBg->Lock(0, 0, (void**)&Pvtx, 0);//この書式は変えないこと

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
	g_pVtxBuffBg->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitBg(void)
{
	//テクスチャの開放
	if (g_pTextureBg != NULL)
	{
		g_pTextureBg->Release();
		g_pTextureBg = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBg(void)
{
	VERTEX_2D*pVtx;
	PLAYER*pPlayer;
	pPlayer = GetPlayer();


	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);
	/*if (pPlayer->pos + (PLAYER_SIZE_X / 2) <= 853.33333334)*/
	//if (GetKeyBoardPress(DIK_D))
	//{
	//	g_fScrollBG += 0.003f;
	//	pVtx[0].tex = D3DXVECTOR2(0.0f + g_fScrollBG, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f + g_fScrollBG, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f + g_fScrollBG, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f + g_fScrollBG, 1.0f);
	//}
	//if (GetKeyBoardPress(DIK_A))
	//{
	//	g_fScrollBG -= 0.003f;
	//	pVtx[0].tex = D3DXVECTOR2(0.0f + g_fScrollBG, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f+ g_fScrollBG, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f + g_fScrollBG, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f + g_fScrollBG, 1.0f);
	//}
	//アンロック
	g_pVtxBuffBg->Unlock();

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(BGVERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBg);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}