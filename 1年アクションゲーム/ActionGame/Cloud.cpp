//=============================================================================
//
// DirectX雛型処理 [Polygon.cpp]
// Author :sugi
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "Cloud.h"
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureCloud = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCloud = NULL;
int g_nCounterAnimCloud;
int g_nPatternAnimCloud;
float g_fScrollCloud;
//=============================================================================
// 初期化処理
//=============================================================================
void InitCloud(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_fScrollCloud = 0.0f;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Cloud.png", &g_pTextureCloud);
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(CLOUDVERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffCloud, NULL);
	//頂点情報へのポインタ
	CLOUDVERTEX_2D *Pvtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	g_pVtxBuffCloud->Lock(0, 0, (void**)&Pvtx, 0);//この書式は変えないこと

												  //頂点座標の設定（右回りで設定する）
	Pvtx[0].pos = D3DXVECTOR3(0.0f, 300.0f, 0.0f);
	Pvtx[1].pos = D3DXVECTOR3(1280.0f, 300.0f, 0.0f);
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
	g_pVtxBuffCloud->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitCloud(void)
{
	//テクスチャの開放
	if (g_pTextureCloud != NULL)
	{
		g_pTextureCloud->Release();
		g_pTextureCloud = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffCloud != NULL)
	{
		g_pVtxBuffCloud->Release();
		g_pVtxBuffCloud = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCloud(void)
{
	VERTEX_2D*pVtx;
	PLAYER*pPlayer;
	pPlayer = GetPlayer();
	g_fScrollCloud += 0.0005f;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffCloud->Lock(0, 0, (void**)&pVtx, 0);
	if (pPlayer->bLife == true)
	{
		if (GetKeyBoardPress(DIK_D))
		{
			g_fScrollCloud += 0.0008f;
		}
		if (GetKeyBoardPress(DIK_A))
		{
			g_fScrollCloud -= 0.0002f;
		}
	}
	pVtx[0].tex = D3DXVECTOR2(0.0f + g_fScrollCloud, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + g_fScrollCloud, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + g_fScrollCloud, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_fScrollCloud, 1.0f);
	//アンロック
	g_pVtxBuffCloud->Unlock();

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawCloud(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffCloud, 0, sizeof(CLOUDVERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureCloud);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}