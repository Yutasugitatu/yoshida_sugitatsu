//=============================================================================
//
// �Q�[�����[�h [mode_game.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_game.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "enemy.h"
#include "ui_meat.h"
#include "ui_daiya.h"
#include "ui.h"
#include "byte_effect.h"
#include "bg_tutorial.h"
#include "dust_particle.h"
#include "field.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CCamera * CGameMode::m_pCamera = NULL;			//�J�����̃|�C���^
CPlayer * CGameMode::m_pPlayer = NULL;			//�v���C���[�̃|�C���^
CEnemy * CGameMode::m_pEnemy = NULL;			//�G�̃|�C���^
CUi * CGameMode::m_pUi = NULL;					//UI�̃|�C���^
CContinue * CGameMode::m_pContinue = NULL;		//�R���e�B�j���[�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameMode::CGameMode()
{
	m_pUi		= NULL;
	m_pLight	= NULL;	//���C�g�̃|�C���^
	m_pTutorial = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameMode::~CGameMode()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CGameMode * CGameMode::Create()
{
	//�Q�[�����[�h�̃|�C���^
	CGameMode * pGameMode = NULL;
	//�����Q�[�����[�h�̃|�C���^��NULL�������ꍇ
	if (pGameMode == NULL)
	{
		//�Q�[�����[�h�̃������m��
		pGameMode = new CGameMode;
		//�����Q�[�����[�h�̃|�C���^��NULL����Ȃ��ꍇ
		if (pGameMode != NULL)
		{
			//�Q�[�����[�h�̏������֐��Ăяo��
			pGameMode->Init();
		}
	}
	//�Q�[�����[�h�̃|�C���^��Ԃ�
	return pGameMode;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CGameMode::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��NULL����Ȃ��ꍇ
	if (pSound != NULL)
	{
		//�^�C�g��BGM�̍Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_GAME);
	}
	//�S�������������֐��Ăяo��
	InitCreateAll();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameMode::Uninit(void)
{
	//�����J�����̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pCamera != NULL)
	{
		//�J�����̏����������֐��Ăяo��
		m_pCamera->Uninit();
		//�J�����̃������j��
		delete m_pCamera;
		//�J�����̃|�C���^��NULL�ɂ���
		m_pCamera = NULL;
	}
	//�������C�g�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pLight != NULL)
	{
		//���C�g�̏����������֐��Ăяo��
		m_pLight->Uninit();
		//���C�g�̃������j��
		delete m_pLight;
		//���C�g�̃|�C���^��NULL�ɂ���
		m_pLight = NULL;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGameMode::Update(void)
{
	//�S�X�V���������֐��Ăяo��
	UpdateCreateAll();
	//�����J�����̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pCamera != NULL)
	{
		//�J������ݒ肷��
		m_pCamera->SetCamera();
		//�J�����̍X�V�����֐��Ăяo��
		m_pCamera->Update();
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// �S�������������֐�
//=============================================================================
void CGameMode::InitCreateAll(void)
{
	if (m_pUi == NULL)
	{
		// �_�C��UI
		m_pUi = CUi::Create(D3DXVECTOR3(DAIYA_POS_X, DAIYA_POS_Y, 0.0f),
			D3DXVECTOR3(DAIYA_SIZE, DAIYA_SIZE, 0.0f),
			CUi::UITYPE_DAIYA);

		// ����UI
		m_pUi = CUi::Create(D3DXVECTOR3(MEAT_POS_X, MEAT_POS_Y, 0.0f),
			D3DXVECTOR3(MEAT_SIZE, MEAT_SIZE, 0.0f),
			CUi::UITYPE_MEAT);
	}
	CMeatUI::Create();
	CDaiyaUI::Create();
	//�������C�g�̃|�C���^��NULL�̏ꍇ
	if (m_pLight == NULL)
	{
		//���C�g�̃������m��
		m_pLight = new CLight;
	}
	//�������C�g�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pLight != NULL)
	{
		//���C�g�̏����������֐��Ăяo��
		m_pLight->Init();
	}
	m_pPlayer = CPlayer::Create();
	m_pEnemy = CEnemy::Create();
	//�����J�����̃|�C���^��NULL�̏ꍇ
	if (m_pCamera == NULL)
	{
		//�J�����̃������m��
		m_pCamera = new CCamera;
	}
	//�����J�����̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pCamera != NULL)
	{
		//�J�����̏����������֐��Ăяo��
		m_pCamera->Init();
	}
	CField::Create();
	m_pTutorial = CTutorialBG::Create();
}

//=============================================================================
// �S�X�V���������֐�
//=============================================================================
void CGameMode::UpdateCreateAll(void)
{
}