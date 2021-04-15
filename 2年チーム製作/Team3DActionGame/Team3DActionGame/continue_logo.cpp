//=============================================================================
//
// �R���e�B�j���[���S [continue_logo.cpp]
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
#include "scene2d.h"
#include "continue_logo.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/CONTINUE.png")										//�e�N�X�`��
#define SIZE (D3DXVECTOR3(700.0f,250.0f,0.0f))										//�T�C�Y
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT - SIZE.y * 3.0f,0.0f))	//�ʒu
#define FLAME (0)																	//�t���[��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CContinueLogo::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CContinueLogo::CContinueLogo()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CContinueLogo::~CContinueLogo()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CContinueLogo::TextureLoad(void)
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
void CContinueLogo::TextureUnload(void)
{
	//�����e�N�X�`����NULL����Ȃ��ꍇ
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CContinueLogo * CContinueLogo::Create(void)
{
	//�R���e�B�j���[���S�̃|�C���^
	CContinueLogo * pContinueLogo = NULL;
	//�����R���e�B�j���[���S�̃|�C���^��NULL�̏ꍇ
	if (pContinueLogo == NULL)
	{
		//�R���e�B�j���[���S�̃������m��
		pContinueLogo = new CContinueLogo;
		//�����R���e�B�j���[���S��NULL����Ȃ��ꍇ
		if (pContinueLogo != NULL)
		{
			//�����������֐��Ăяo��
			pContinueLogo->Init();
			//�ʒu��ݒ肷��
			pContinueLogo->SetPosition(POSITION);
			//�T�C�Y��ݒ肷��
			pContinueLogo->SetSize(SIZE);
		}
	}
	//�R���e�B�j���[���S�̃|�C���^��Ԃ�
	return pContinueLogo;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CContinueLogo::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�V�[��2D�̏����������֐��Ăяo��
	CScene2d::Init();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CContinueLogo::Uninit(void)
{
	//�V�[��2D�̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CContinueLogo::Update(void)
{
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�V�[��2D�̍X�V�����֐��Ăяo��
	CScene2d::Update();
	//�����v���C���[���R���e�B�j���[������
	if (pPlayer->GetContinue() == true)
	{
		//�I�������֐��Ăяo��
		Uninit();
		return;
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CContinueLogo::Draw(void)
{
	//�V�[��2D�̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}
