#include "Input.h"
#include "result.h"
#include "game.h"
#include "player.h"
#include "goal.h"
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点情報へのポインタ
	GOALVERTEX_2D *Pvtx;
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Goal.png", &g_pTextureGoal);
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(GOALVERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGoal, NULL);
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&Pvtx, 0);//この書式は変えないこと
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
	g_pVtxBuffGoal->Unlock();

}
void UninitGoal(void)
{
	//テクスチャの開放
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}
	//テクスチャの開放
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}
void UpdateGoal(void)
{
	if (GetKeyBoardTrigger(DIK_RETURN))
	{
		InitGame();
	}
}
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER*pPlayer;
	pPlayer = GetPlayer();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(GOALVERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureGoal);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}