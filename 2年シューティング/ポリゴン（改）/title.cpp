//-----------------------------------------------
//
//  [title.cpp]
//  author:�����I��
//
//-----------------------------------------------
#include "input.h"
#include "title.h"
#include "game.h"
#include "sound.h"
#include "main.h"
#include "bg.h"
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
LPDIRECT3DTEXTURE9  CTitle::m_pTexture = NULL;
CTitle::CTitle()
{
	m_apScene2D = NULL;
}

CTitle::~CTitle()
{

}
HRESULT CTitle::Load()
{
//�錾
LPDIRECT3DDEVICE9 pDevice;
CRenderer *pRenderer = CManager::GetRenderer();
pDevice = pRenderer->GetDevice();

//�e�N�X�`���̓ǂݍ���
D3DXCreateTextureFromFile(pDevice, "texture/Title.png", &m_pTexture);
return S_OK;
}

void CTitle::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

CTitle * CTitle::Create(D3DXVECTOR3 pos)
{
	CTitle *pTitle = NULL;
	pTitle = new CTitle;
	pTitle->Init(pos);
	return pTitle;
}

HRESULT CTitle::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{
	m_apScene2D = new CScene2d;
	m_apScene2D->Init(pos, SCREEN_WIDTH ,SCREEN_HEIGHT);
	m_apScene2D->BindTexture(m_pTexture);
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM000);


	return S_OK;
}

void CTitle::Uninit(void)
{
	//�w�i�̔j��
	Release();
}
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if (pInputKeyboard->GetKeyBoardTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_GAME);

		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
		pSound->StopSound(CSound::SOUND_LABEL_BGM000);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}