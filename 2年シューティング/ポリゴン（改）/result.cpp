//-----------------------------------------------
//
//  [result.cpp]
//  author:杉立悠太
//
//-----------------------------------------------
#include "Input.h"
#include "result.h"
#include "game.h"
#include "sound.h"
#include "bg.h"
#include "title.h"
#include "manager.h"
#include "fade.h"
#include "renderer.h"
#include "scene2d.h"
LPDIRECT3DTEXTURE9  CResult::m_pTexture = NULL;
CResult::CResult()
{
	m_apScene2D = NULL;
}

CResult::~CResult()
{

}

CResult * CResult::Create(D3DXVECTOR3 pos)
{
	CResult *pResult = NULL;
	pResult = new CResult;
	pResult->Init(pos);
	return pResult;
}
HRESULT CResult::Load(void)
{
	//宣言
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();
	D3DXCreateTextureFromFile(pDevice,"texture/bg.png", &m_pTexture);
	return S_OK;
}
void CResult::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{
	m_apScene2D = new CScene2d;
	m_apScene2D->Init(pos,1280, 720);
	m_apScene2D->BindTexture(m_pTexture);
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM002);

return S_OK;
}
void CResult::Uninit(void)
{
	Release();
}
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if (pInputKeyboard->GetKeyBoardTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		CSound *pSound = CManager::GetSound();
		pSound->StopSound(CSound::SOUND_LABEL_BGM002);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
}

