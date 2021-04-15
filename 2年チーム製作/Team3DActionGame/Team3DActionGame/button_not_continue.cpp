//=============================================================================
//
// �R���e�B�j���[���Ȃ��{�^�� [button_not_continue.cpp]
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
#include "renderer.h"
#include "sound.h"
#include "button_not_continue.h"
#include "needle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/NO.png")

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CNotContinueButton::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNotContinueButton::CNotContinueButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNotContinueButton::~CNotContinueButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CNotContinueButton::TextureLoad(void)
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
void CNotContinueButton::TextureUnload(void)
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
CNotContinueButton * CNotContinueButton::Create(D3DXVECTOR3 Position)
{
	//�R���e�B�j���[���Ȃ��{�^���̃|�C���^
	CNotContinueButton * pNotContinueButton = NULL;
	//�R���e�B�j���[���Ȃ��{�^���̃|�C���^��NULL�̏ꍇ
	if (pNotContinueButton == NULL)
	{
		//�R���e�B�j���[���Ȃ��{�^���̃������m��
		pNotContinueButton = new CNotContinueButton;
		//�R���e�B�j���[���Ȃ��{�^���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pNotContinueButton != NULL)
		{
			//�R���e�B�j���[���Ȃ��{�^���̈ʒu�ݒ�
			pNotContinueButton->SetPosition(Position);
			//�R���e�B�j���[���Ȃ��{�^���̏����������֐��Ăяo��
			pNotContinueButton->Init();
		}
	}
	//�R���e�B�j���[���Ȃ��{�^���̃|�C���^��Ԃ�
	return pNotContinueButton;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CNotContinueButton::Init(void)
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
void CNotContinueButton::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CButton::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CNotContinueButton::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CButton::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CNotContinueButton::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CButton::Draw();
}

//=============================================================================
// �v���X�����֐�
//=============================================================================
void CNotContinueButton::Press(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��NULL����Ȃ��ꍇ
	if (pSound != NULL)
	{
		//���艹�̍Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	}
	//�^�C�g���Ɉړ�
	CManager::StartFade(CManager::MODE_TITLE);
}
