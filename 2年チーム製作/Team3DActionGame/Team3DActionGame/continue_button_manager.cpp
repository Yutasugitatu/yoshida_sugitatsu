//=============================================================================
//
// �R���e�B�j���[�{�^���}�l�[�W���[ [continue_button_manager.cpp]
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
#include "keyboard.h"
#include "joystick.h"
#include "continue_button_manager.h"
#include "button_continue.h"
#include "button_not_continue.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 740.0f, 0.0f))		//�X�^�[�g�{�^���̈ʒu
#define TUTORIAL_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 820.0f, 0.0f))	//�`���[�g���A���{�^���̈ʒu
#define RANKING_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f))	//�����L���O�{�^���̈ʒu
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 980.0f, 0.0f))		//�I���{�^���̈ʒu

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CContinueButtonManager::CContinueButtonManager()
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//�{�^���̃|�C���^
	m_nButton = BUTTON_NONE;						//�{�^��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CContinueButtonManager::~CContinueButtonManager()
{
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CContinueButtonManager * CContinueButtonManager::Create(void)
{
	//�^�C�g���{�^���}�l�[�W���[�̃|�C���^
	CContinueButtonManager * pTitleButtonManager = NULL;
	//�^�C�g���{�^���}�l�[�W���[�|�C���^��NULL�̏ꍇ
	if (pTitleButtonManager == NULL)
	{
		//�^�C�g���{�^���}�l�[�W���[�̃������m��
		pTitleButtonManager = new CContinueButtonManager;
		//�^�C�g���{�^���}�l�[�W���[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pTitleButtonManager != NULL)
		{
			//�^�C�g���{�^���}�l�[�W���[�̏����������֐��Ăяo��
			pTitleButtonManager->Init();
		}
	}
	//�^�C�g���{�^���}�l�[�W���[�̃|�C���^��Ԃ�
	return pTitleButtonManager;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CContinueButtonManager::Init(void)
{
	//�����S�������֐��Ăяo��
	InitCreateAll();
	//�{�^���̏����ݒ�
	m_nButton = BUTTON_CONTINUE;
	//�{�^���̏����I�������֐��Ăяo��
	m_apButton[m_nButton]->SelectColor();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CContinueButtonManager::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CContinueButtonManager::Update(void)
{
	//�{�^���̍ő吔����
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//�{�^���̑I������ĂȂ����̐F�ύX�����֐��Ăяo��
		m_apButton[nCount]->NotSelectColor();
	}
	//�{�^���̑I�����F�ύX�����֐��Ăяo��
	m_apButton[m_nButton]->SelectColor();
	//���͏����֐��Ăяo��
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CContinueButtonManager::Draw(void)
{
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CContinueButtonManager::Input(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_UP) || lpDIDevice != NULL &&js.rgdwPOV[0] == 0)
	{
		//���݂̃{�^�������Z����
		m_nButton--;
		//�������݂̃{�^�����X�^�[�g�{�^����艺��������
		if (m_nButton < BUTTON_CONTINUE)
		{
			//���݂̃{�^�����I���{�^���ɂ���
			m_nButton = BUTTON_NOT_CONTINUE;
		}
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->SelectSound();
	}
	//�����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN) || lpDIDevice != NULL &&js.rgdwPOV[0] == 18000)
	{
		//���݂̃{�^�������Z����
		m_nButton++;
		//�������݂̃{�^�����I���{�^�����z������
		if (m_nButton > BUTTON_NOT_CONTINUE)
		{
			//���݂̃{�^�����X�^�[�g�{�^���ɂ���
			m_nButton = BUTTON_CONTINUE;
		}
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->SelectSound();
	}
	//����ENTER�L�[���̓W���C�X�e�B�b�N��A�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//�{�^���̃v���X�����֐��Ăяo��
		m_apButton[m_nButton]->Press();
		//�{�^���̑�������
		for (int nCount = BUTTON_CONTINUE; nCount < BUTTON_MAX; nCount++)
		{
			//�e�{�^���̏I�������֐��Ăяo��
			m_apButton[nCount]->Uninit();
		}
		//�I�������֐��Ăяo��
		Uninit();
		return;
	}
}

//=============================================================================
// �������������֐�
//=============================================================================
void CContinueButtonManager::InitCreateAll(void)
{
	//�X�^�[�g�{�^���̐���
	m_apButton[BUTTON_CONTINUE] = CContinueButton::Create(START_BUTTON_POSITION);
	//�`���[�g���A���{�^���̐���
	m_apButton[BUTTON_NOT_CONTINUE] = CNotContinueButton::Create(TUTORIAL_BUTTON_POSITION);
}