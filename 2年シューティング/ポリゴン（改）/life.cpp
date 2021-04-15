//-----------------------------------------------
//
//  体力[life.cpp]
//  author:杉立悠太
//
//-----------------------------------------------
#include "life.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "bullet.h"
LPDIRECT3DTEXTURE9  CLife::m_pTexture = NULL;
CLife::CLife()
{
}

CLife::~CLife()
{

}

CLife * CLife::Create(D3DXVECTOR3 pos)
{
	CLife*pLife  = NULL;
	pLife = new CLife;
	pLife->Init(pos, ENEMY_SIZE, ENEMY_SIZE);
	return pLife;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{
	//玉の初期設定
	CScene2d::Init(pos, ENEMY_SIZE, ENEMY_SIZE);
	CScene2d::BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_LIFE);
	//SetObjType(CScene::OBJTYPE_PLAYER);
	return S_OK;
}

void CLife::Uninit(void)
{
	CScene2d::Uninit();
}

void CLife::Update(void)
{
	//移動
	D3DXVECTOR3 pos;
	pos = GetPosition();
	//位置更新
	SetPosition(pos);
}
//=============================================================================
// 描画処理
//=============================================================================
void CLife::Draw(void)
{
	CScene2d::Draw();
}
void CLife::Load(void)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "texture/life.png", &m_pTexture);

}
void CLife::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}