#include "Input.h"
#include "result.h"
#include "game.h"
#include "player.h"
#include "sound.h"
#include "fade.h"
#include "title.h"
#include "Block.h"
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_TYPE_RESULT] = { 0 };
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
RESULTSELECT g_nResult;
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点情報へのポインタ
	RESULTVERTEX_2D *Pvtx;
	g_nResult = RESULTSELECT_YES;
	int nCnttex;
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "GameOver.png", &g_pTextureResult[RESULTSELECT_NONE]);
	D3DXCreateTextureFromFile(pDevice, "Yes.png", &g_pTextureResult[RESULTSELECT_YES]);
	D3DXCreateTextureFromFile(pDevice, "No.png", &g_pTextureResult[RESULTSELECT_NO]);
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(RESULTVERTEX_2D)*NUM_VERTEX*MAX_TYPE_RESULT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL);
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	g_pVtxBuffResult->Lock(0, 0, (void**)&Pvtx, 0);//この書式は変えないこと
												   //頂点座標の設定（右回りで設定する）
	Pvtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Pvtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	Pvtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	Pvtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		//3//ノーマル
		Pvtx[4].pos = D3DXVECTOR3(200.0f, 500.0f, 0.0f);
		Pvtx[5].pos = D3DXVECTOR3(600.0f, 500.0f, 0.0f);
		Pvtx[6].pos = D3DXVECTOR3(200.0f, 620.0f, 0.0f);
		Pvtx[7].pos = D3DXVECTOR3(600.0f, 620.0f, 0.0f);
		//3//ノーマル
		Pvtx[8].pos = D3DXVECTOR3(700.0f, 500.0f, 0.0f);
		Pvtx[9].pos = D3DXVECTOR3(1050.0f, 500.0f, 0.0f);
		Pvtx[10].pos = D3DXVECTOR3(700.0f, 620.0f, 0.0f);
		Pvtx[11].pos = D3DXVECTOR3(1050.0f, 620.0f, 0.0f);
	
	for (nCnttex = 0; nCnttex < MAX_TYPE_RESULT; nCnttex++)
	{
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
		Pvtx += 4;
	}
	//頂点データをアンロックする
	g_pVtxBuffResult->Unlock();

}
void UninitResult(void)
{
	int nCnttex;
	//テクスチャの開放
		for (nCnttex = 0; nCnttex < MAX_TYPE_RESULT; nCnttex++)
		{
			if (g_pTextureResult[nCnttex] != NULL)
			{
				g_pTextureResult[nCnttex]->Release();
				g_pTextureResult[nCnttex] = NULL;
			}

		}
	//テクスチャの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
void UpdateResult(void)
{
	FADE pFade;
	pFade = GetFade();
	RESULTVERTEX_2D *Pvtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	g_pVtxBuffResult->Lock(0, 0, (void**)&Pvtx, 0);//この書式は変えないこと
	if (g_nResult == RESULTSELECT_YES)
	{
		//3//ノーマル
		Pvtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		if (GetKeyBoardTrigger(DIK_RETURN) && pFade == FADE_NONE)
		{
			SetFade(MODE_GAME);
			InitGame();
		}
	}
	if (g_nResult == RESULTSELECT_NO)
	{
		if (GetKeyBoardTrigger(DIK_RETURN) && pFade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
			InitGame();
			InitTitle();
		}
	}
	if (GetKeyBoardTrigger(DIK_A) || GetKeyBoardTrigger(DIK_LEFT))
	{
		InitPlayer();
		InitBlock();
		g_nResult = RESULTSELECT_YES;
		//PlaySound(SOUND_LABEL_SELECT);
		//3//ノーマル
		Pvtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//3//ノーマル
		Pvtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 55);
	}
	if (GetKeyBoardTrigger(DIK_D)|| GetKeyBoardTrigger(DIK_RIGHT))
	{
		g_nResult = RESULTSELECT_NO;
		//PlaySound(SOUND_LABEL_SELECT);
		//3//ノーマル
		Pvtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		Pvtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 55);
		//3//ノー
		Pvtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		Pvtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	//頂点データをアンロックする
	g_pVtxBuffResult->Unlock();
}
void DrawResult(void)
{
	int nCnttex;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER*pPlayer;
	pPlayer = GetPlayer();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(RESULTVERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (nCnttex = 0; nCnttex < MAX_TYPE_RESULT; nCnttex++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[nCnttex]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnttex*4, NUM_POLYGON);
	}
}