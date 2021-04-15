//-----------------------------------------------
//
//  [manager.cpp]
//  author:杉立悠太
//
//-----------------------------------------------
#include "manager.h"
#include "input.h"
#include "main.h"
#include "renderer.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "player.h"
#include "renderer.h"
#include "sound.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "finish.h"
#include "bomb.h"
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CRenderer *CManager::m_pRenderer = NULL;
CSound *CManager::m_pSound = NULL;
CTitle *CManager::m_pTitle = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CFinish *CManager::m_pFinish = NULL;
CFade *CManager::m_pFade = NULL;
CManager::MODE CManager::m_pMode = MODE_TITLE;

CManager::CManager()
{

}
CManager::~CManager()
{
	
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	//生成
	m_pRenderer = new CRenderer;
	m_pSound = new CSound;
	// 初期化処理
	m_pRenderer->Init(hWnd, TRUE);
	m_pSound->InitSound(hWnd);
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);
	CPlayer::Load();
	CBullet::Load();
	CExplosion::Load();
	CBg::Load();
	CEnemy::Load();
	CNumber::Load();
	CLife::Load();
	CBomb::Load();
	CTitle::Load();
	CResult::Load();
	m_pFade = new CFade;
	m_pFade->InitFade(MODE_TITLE);
	return S_OK;

}
void CManager::Uninit(void)
{
	CScene::ReleaseAll();
	CPlayer::UnLoad();
	CBullet::UnLoad();
	CExplosion::UnLoad();
	CBg::UnLoad();
	CEnemy::UnLoad();
	CNumber::UnLoad();
	CLife::UnLoad();
	CBomb::UnLoad();
	CTitle::UnLoad();
	CResult::UnLoad();
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	//終了処理
	m_pRenderer->Uninit();

	delete m_pRenderer;
	m_pRenderer = NULL;
}
void CManager::Update(void)
{
	m_pInputKeyboard->Update();
	m_pRenderer->Update();
	m_pFade->UpdateFade();
}
//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// 描画処理
	m_pRenderer->Draw();
	m_pFade->DrawFade();
}

CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//レンダラ＾の取得
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
//モードの設定
//=============================================================================
void CManager::SetMode(MODE mode)
{
	//現在のモードの情報を削除する
	switch (m_pMode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	case MODE_FINISH:
		if (m_pFinish != NULL)
		{
			m_pFinish->Uninit();
			m_pFinish = NULL;
		}
		break;
	}

	CScene::ReleaseAll();

	//指定されたモードに設定する
	m_pMode = mode;

	//指定されたモードの情報を生成する
	switch (m_pMode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
		m_pTitle = CTitle::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));
		}
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{
		m_pGame = CGame::Create();
		}
		
		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0));
		}
		break;
	case MODE_FINISH:
		if (m_pFinish == NULL)
		{
			m_pFinish = CFinish::Create();
		}
		break;
	}
}