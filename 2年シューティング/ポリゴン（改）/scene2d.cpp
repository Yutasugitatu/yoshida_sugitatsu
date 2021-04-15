//=============================================================================
//
// [Scene2d.cpp]
// Author : 杉立悠太
//
//=============================================================================

//======================
//マクロ定義
//======================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bg.h"
//コンストラクタ
CScene2d::CScene2d(int nPriority):CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//デストラクタ
CScene2d::~CScene2d()
{

}
//====================
//初期化処理
//====================
HRESULT CScene2d::Init(D3DXVECTOR3 pos,int nSizeX, int nSizeY)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();
	
	// ポリゴンの位置を設定
	m_pos = pos;

	m_nSizeX = nSizeX;
	m_nSizeY = nSizeY;

	
	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_nSizeX, m_pos.y - m_nSizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_nSizeX, m_pos.y - m_nSizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_nSizeX, m_pos.y + m_nSizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_nSizeX, m_pos.y + m_nSizeY, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================
// 終了処理
//====================
void CScene2d::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}
//====================
// 更新処理
//====================
void  CScene2d::Update(void)
{
	
}
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//====================
// 描画処理
//====================
void CScene2d::Draw(void)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}
void CScene2d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_nSizeX/2, m_pos.y - m_nSizeY/2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_nSizeX/2, m_pos.y - m_nSizeY/2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_nSizeX/2, m_pos.y + m_nSizeY/2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_nSizeX/2, m_pos.y + m_nSizeY/2, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
void CScene2d::SetTexturePos(D3DXVECTOR2 TexMin, D3DXVECTOR2 TexMax)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(TexMin.x, TexMin.y);
	pVtx[1].tex = D3DXVECTOR2(TexMax.x, TexMin.y);
	pVtx[2].tex = D3DXVECTOR2(TexMin.x, TexMax.y);
	pVtx[3].tex = D3DXVECTOR2(TexMax.x, TexMax.y);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

