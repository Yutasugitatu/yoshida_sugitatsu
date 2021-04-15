//-----------------------------------------------
//
//  背景[number.cpp]
//  author:杉立悠太
//
//-----------------------------------------------
#include "number.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "score.h"
LPDIRECT3DTEXTURE9  CNumber::m_pTexture = NULL;
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}

CNumber::~CNumber()
{

}


CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CNumber *pNumber = NULL;
	pNumber = new CNumber;
	pNumber->Init(pos,size);
	return pNumber;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ポリゴンの位置を設定
	m_pos = pos;
	m_size = size;

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y - m_size.y/2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y - m_size.y/2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y + m_size.y/2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y + m_size.y/2, 0.0f);


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
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void CNumber::Update(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void CNumber::Draw(void)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	//CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

HRESULT CNumber::Load(void)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	/*CRenderer *pRenderer = CManager::GetRenderer();*/
	pDevice = CManager::GetRenderer()->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,"texture/number000.png", &m_pTexture);
	return S_OK;
}

void CNumber::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

void CNumber::SetNumber(int nNumber)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (float)(0.1*nNumber), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (float)(0.1*nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (float)(0.1*nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (float)(0.1*nNumber), 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
