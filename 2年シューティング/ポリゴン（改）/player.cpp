//-----------------------------------------------
//
//  ���@[player.cpp]
//  author:�����I��
//
//-----------------------------------------------
#include "player.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "life.h"
#include "game.h"
#include "fade.h"
#include "bomb.h"
LPDIRECT3DTEXTURE9  CPlayer::m_pTexture = NULL;

CPlayer::CPlayer(int nPriority) :CScene2d(nPriority)
{
	m_invinsible = false;
	m_Life = 0;
	m_second = 0;
	m_nBullet = 0;
	m_change = 0;
	state = STATE_NORMAL;
	memset(&m_pLife,0,sizeof(m_pLife));
}
CPlayer::~CPlayer()
{

}
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;
	pPlayer->Init(pos,50,50);
	for (int nCnt = 0; nCnt < PLAYER_LIFE; nCnt++)
	{
		pPlayer->m_pLife[nCnt] = CLife::Create(D3DXVECTOR3((nCnt*50.0f) + 50.0f, 50.0f, 0.0f));
	}
	return pPlayer;

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, int nSizeX, int nSizeY)
{
	m_Life = PLAYER_LIFE;
	CScene2d::Init(pos,50,50);
	CScene2d::BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}
void CPlayer::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CSound*pSound = CManager::GetSound();
	D3DXVECTOR3 pos = CScene2d::GetPosition();
	CScore *pScore = CGame::GetScore();
	if (pos.x - 30.0f <= 0)
	{
		pos.x = 30.0f;
	}
	if (pos.x + 30.0f >= SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH -30.0f;
	}
	if (pos.y - 30.0f <= 0)
	{
		pos.y = 30.0f;
	}
	if (pos.y + 30.0f >= SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT -30.0f;
	}
	if (pInputKeyboard->GetKeyBoardPress(DIK_D)){//�E�ړ�
		pos.x += 7.0f;
	}
	if (pInputKeyboard->GetKeyBoardPress(DIK_A)){//�E�ړ�
		pos.x -= 7.0f;
	}
	if (pInputKeyboard->GetKeyBoardPress(DIK_W)){//�E�ړ�
		pos.y -= 7.0f;
	}
	if (pInputKeyboard->GetKeyBoardPress(DIK_S)){//�E�ړ�
		pos.y += 7.0f;
	}
	m_second++;
	if (m_second >= 45)
	{
		if (pInputKeyboard->GetKeyBoardTrigger(DIK_SPACE))
		{
			m_second = 0;
			CBomb::Create(pos);
			pSound->PlaySound(CSound::SOUND_LABEL_PLANT);
		}
	}
	
	CScene2d::SetPosition(pos);
	CScene2d::Update();
	if (m_Life <= 0)
	{
		state = STATE_DEATH;
	}
	switch (state)
	{
	case STATE_DEATH:
		m_change++;
		pSound->PlaySound(CSound::SOUND_LABEL_DETH);
		pSound->StopSound(CSound::SOUND_LABEL_BGM001);
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
		Uninit();
		return;
		break;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2d::Draw();
}
void CPlayer::Load(void)
{
	//�錾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "texture/jiki.png", &m_pTexture);
}
void CPlayer::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release(); 
		m_pTexture = NULL;
	}
}

void CPlayer::HitPlayer(int nLife)
{
	m_Life -= nLife;
	if (m_Life >= 0)
	{
		m_pLife[m_Life]->Uninit();
	}
	
}
