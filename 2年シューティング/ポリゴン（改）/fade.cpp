//=============================================================================
//
// DirectX雛型処理 [Polygon.cpp]
// Author :杉立悠太
//
//=============================================================================
#include "main.h"
#include "Player.h"
#include "bg.h"
#include "input.h"
#include "title.h"
#include "fade.h"
#include "renderer.h"
#include "manager.h"
//=============================================================================
// グローバル変数
//=============================================================================
//コンストラクタ
CFade::CFade()
{
	m_fade = FADE_OUT;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}
//デストラクタ
CFade::~CFade()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
void CFade::InitFade(CManager::MODE ModeNext)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffFade, NULL);
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを会得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えないこと

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

	//頂点データをアンロックする
	m_pVtxBuffFade->Unlock();
	m_ModeNext = ModeNext;
}
//=============================================================================
// 終了処理
//=============================================================================
void CFade::UninitFade(void)
{

}
//
//CFade::FADE CFade::GetFade(void)
//{
//	return m_fade;
//}
void CFade::SetFade(CManager::MODE ModeNext)
{
	m_fade = FADE_OUT;
	m_ModeNext = ModeNext;
}
//=============================================================================
// 更新処理
//=============================================================================
void CFade::UpdateFade(void)
{
	VERTEX_2D*pVtx;

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_colorFade.a -= FADE_RATE;
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_colorFade.a += FADE_RATE;
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;

				CManager::SetMode(m_ModeNext);
			}
		}
	}


	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;
	//アンロック
	m_pVtxBuffFade->Unlock();

}
//=============================================================================
// 描画処理
//=============================================================================
void CFade::DrawFade(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定

	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTextureFade);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}