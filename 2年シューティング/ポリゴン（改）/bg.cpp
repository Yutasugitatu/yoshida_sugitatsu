//-----------------------------------------------
//
//  背景[bg.cpp]
//  author:杉立悠太
//
//-----------------------------------------------

#include "main.h"
#include "bg.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"
//LPDIRECT3DTEXTURE9  CBg::m_pTexture = NULL;
LPDIRECT3DTEXTURE9  CBg::m_apTexture[TYPE_MAX] = {};
//ロード
HRESULT CBg::Load(void)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "texture/bg.png", &m_apTexture[TYPE_BG1]);
	//D3DXCreateTextureFromFile(pDevice, "bg.png", &m_apTexture[TYPE_BG2]);
	//D3DXCreateTextureFromFile(pDevice, "bg.png", &m_apTexture[TYPE_BG3]);
	return S_OK;
}
//生成処理
CBg* CBg::Create(D3DXVECTOR3 pos)
{
	CBg *pBg = NULL;
	pBg = new CBg;
	pBg->Init(pos, SCREEN_WIDTH, SCREEN_HEIGHT);
	return pBg;
}
//アンロード
void CBg::UnLoad(void)
{
	////テクスチャの破棄
	if (m_apTexture != NULL)
	{
		for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//コンストラクタ
CBg::CBg()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
		m_fScroll[nCnt] = 0.0f;
	}
	m_nType = TYPE_BG1;
}
//デストラクタ
CBg::~CBg()
{

}
//初期化処理
HRESULT CBg::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2d;
		m_apScene2D[nCnt]->Init(pos, SCREEN_WIDTH, SCREEN_HEIGHT);
		m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}
	//m_nType = TYPE_NUM;
	return S_OK;
}
//終了処理
void CBg::Uninit(void)
{
	Release();
}
//更新処理
void CBg::Update(void)
{
	//BGTYPE m_nType = TYPE_BG1;

	//m_fScroll[TYPE_BG1] += 0.002f;
	//m_fScroll[TYPE_BG2] -= 0.032f;
	//m_fScroll[TYPE_BG3] += 0.02f;

	////描画のポインタの受けとり
	//for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	//{
	//	//背景を動かす処理
	//	D3DXVECTOR2 min = D3DXVECTOR2(0.0f, 0.0f + m_fScroll[nCnt]);
	//	D3DXVECTOR2 Max = D3DXVECTOR2(1.0f, 1.0f + m_fScroll[nCnt]);
	//	m_apScene2D[nCnt]->SetTexturePos(min, Max);
	//}
}
//描画処理
void CBg::Draw(void)
{

}

