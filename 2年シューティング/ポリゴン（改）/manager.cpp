//-----------------------------------------------
//
//  [manager.cpp]
//  author:�����I��
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
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	//����
	m_pRenderer = new CRenderer;
	m_pSound = new CSound;
	// ����������
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
	//�I������
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
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �`�揈��
	m_pRenderer->Draw();
	m_pFade->DrawFade();
}

CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//�����_���O�̎擾
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
//���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	//���݂̃��[�h�̏����폜����
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

	//�w�肳�ꂽ���[�h�ɐݒ肷��
	m_pMode = mode;

	//�w�肳�ꂽ���[�h�̏��𐶐�����
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