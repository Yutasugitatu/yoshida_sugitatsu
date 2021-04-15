//=============================================================================
//
// �R���e�B�j���[�{�^�� [button_continue.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "sound.h"
#include "button_continue.h"
#include "player.h"
#include "enemy.h"
#include "continue.h"
#include "needle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/YES.png")

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CContinueButton::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CContinueButton::CContinueButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CContinueButton::~CContinueButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CContinueButton::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE,						// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CContinueButton::TextureUnload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CContinueButton * CContinueButton::Create(D3DXVECTOR3 Position)
{
	//�R���e�B�j���[�{�^���̃|�C���^
	CContinueButton * pContinueButton = NULL;
	//�R���e�B�j���[�{�^���̃|�C���^��NULL�̏ꍇ
	if (pContinueButton == NULL)
	{
		//�R���e�B�j���[�{�^���̃������m��
		pContinueButton = new CContinueButton;
		//�R���e�B�j���[�{�^���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pContinueButton != NULL)
		{
			//�R���e�B�j���[�{�^���̈ʒu�ݒ�
			pContinueButton->SetPosition(Position);
			//�R���e�B�j���[�{�^���̏����������֐��Ăяo��
			pContinueButton->Init();
		}
	}
	//�R���e�B�j���[�{�^���̃|�C���^��Ԃ�
	return pContinueButton;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CContinueButton::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//�{�^���̏����������֐��Ăяo��
	CButton::Init();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CContinueButton::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CButton::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CContinueButton::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CButton::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CContinueButton::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CButton::Draw();
}

//=============================================================================
// �v���X�����֐�
//=============================================================================
void CContinueButton::Press(void)
{
	CContinue * pContinue = CGameMode::GetContinue();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�G�̎擾
	CEnemy * pEnemy = CGameMode::GetEnemy();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��NULL����Ȃ��ꍇ
	if (pSound != NULL)
	{
		//���艹�̍Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	}
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̃R���e�B�j���[��true�ɂ���
		pPlayer->SetbContinue(true);
	}
	//�����G�̃|�C���^��NULL����Ȃ��ꍇ
	if (pEnemy != NULL)
	{
		//�G�̃R���e�B�j���[��true�ɂ���
		pEnemy->SetbContinue(true);
	}
	pContinue->Uninit();
}
