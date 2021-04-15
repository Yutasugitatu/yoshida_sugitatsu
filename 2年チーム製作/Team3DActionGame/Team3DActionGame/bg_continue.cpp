//=============================================================================
//
// �R���e�B�j���[�w�i [bg_continue.cpp]
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
#include "bg_continue.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/ContinueBG.png")								//�e�N�X�`��
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))					//�T�C�Y
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))		//�ʒu
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,0.5f))								//�F
#define FLAME (0)															//�t���[��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CContinueBG::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CContinueBG::CContinueBG()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CContinueBG::~CContinueBG()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CContinueBG::TextureLoad(void)
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
void CContinueBG::TextureUnload(void)
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
CContinueBG * CContinueBG::Create(void)
{
	//�R���e�B�j���[�w�i�̃|�C���^
	CContinueBG * pContinueBG = NULL;
	//�����R���e�B�j���[�w�i�̃|�C���^��NULL�̏ꍇ
	if (pContinueBG == NULL)
	{
		//�R���e�B�j���[�w�i�̃������m��
		pContinueBG = new CContinueBG;
		//�����R���e�B�j���[�w�i��NULL����Ȃ��ꍇ
		if (pContinueBG != NULL)
		{
			//�����������֐��Ăяo��
			pContinueBG->Init();
			//�ʒu��ݒ肷��
			pContinueBG->SetPosition(POSITION);
			//�T�C�Y��ݒ肷��
			pContinueBG->SetSize(SIZE);
			//�F��ݒ肷��
			pContinueBG->SetColor(COLOR);
		}
	}
	//�R���e�B�j���[�w�i�̃|�C���^��Ԃ�
	return pContinueBG;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CContinueBG::Init(void)
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
void CContinueBG::Uninit(void)
{
	//�V�[��2D�̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CContinueBG::Update(void)
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
void CContinueBG::Draw(void)
{
	//�V�[��2D�̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}
