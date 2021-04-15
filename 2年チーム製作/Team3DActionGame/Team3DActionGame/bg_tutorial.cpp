//=============================================================================
//
// �`���[�g���A���w�i [bg_tutorial.cpp]
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
#include "Keyboard.h"
#include "joystick.h"
#include "bg_tutorial.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_KEYBOARD	("Data/Texture/TutorialBG0.png")						// �e�N�X�`��
#define TEXTURE_CONTROLLER	("Data/Texture/TutorialBG1.png")						// �e�N�X�`��1
#define SIZE				(D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))			// �T�C�Y
#define POSITION			(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	// �ʒu
#define COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// �F
#define FLAME				(0)														// �t���[��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTutorialBG::m_pTexture[TEX_TYPE_MAX] = {};						//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorialBG::CTutorialBG(int nPriority) : CScene2d(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorialBG::~CTutorialBG()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CTutorialBG::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_KEYBOARD,									// �t�@�C���̖��O
		&m_pTexture[TEX_TYPE_KEYBOARD]);					// �ǂݍ��ރ������[
															// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_CONTROLLER,									// �t�@�C���̖��O
		&m_pTexture[TEX_TYPE_CONTROLLER]);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CTutorialBG::TextureUnload(void)
{
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		//�����e�N�X�`����NULL����Ȃ��ꍇ
		if (m_pTexture[nCnt] != NULL)
		{
			//�e�N�X�`���̔j�������֐��Ăяo��
			m_pTexture[nCnt]->Release();
			//�e�N�X�`����NULL�ɂ���
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CTutorialBG * CTutorialBG::Create(void)
{
	//�^�C�g���w�i�̃|�C���^
	CTutorialBG * pTitleBG = NULL;
	//�����^�C�g���w�i�̃|�C���^��NULL�̏ꍇ
	if (pTitleBG == NULL)
	{
		//�^�C�g���w�i�̃������m��
		pTitleBG = new CTutorialBG;
		//�����^�C�g���w�i��NULL����Ȃ��ꍇ
		if (pTitleBG != NULL)
		{
			//�ʒu��ݒ肷��
			pTitleBG->SetPosition(POSITION);

			//�T�C�Y��ݒ肷��
			pTitleBG->SetSize(SIZE);

			//�F��ݒ肷��
			pTitleBG->SetColor(COLOR);

			// �I�u�W�F�^�C�v�ݒ�
			pTitleBG->SetObjType(OBJTYPE_TUTORIAL);

			//�����������֐��Ăяo��
			pTitleBG->Init();
		}
	}
	//�^�C�g���w�i�̃|�C���^��Ԃ�
	return pTitleBG;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CTutorialBG::Init(void)
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

	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();

	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();

	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();

	DIJOYSTATE js;

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	// NULL�łȂ��ꍇ
	if (lpDIDevice != NULL)
	{
		//�e�N�X�`���̊��蓖��
		BindTexture(m_pTexture[TEX_TYPE_CONTROLLER]);
	}
	// NULL�̏ꍇ
	if (lpDIDevice == NULL)
	{
		//�e�N�X�`���̊��蓖��
		BindTexture(m_pTexture[TEX_TYPE_KEYBOARD]);
	}

	// �S�̂̍X�V��~
	CScene::SetUpdateStop(true);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CTutorialBG::Uninit(void)
{
	//�V�[��2D�̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CTutorialBG::Update(void)
{
	//�V�[��2D�̍X�V�����֐��Ăяo��
	CScene2d::Update();

	//�L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();

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
	//����ENTER��A�{�^�����������Ƃ�
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_A))
	{
		// �S�̂̍X�V��~
		CScene::SetUpdateStop(false);
		// �I��
		Uninit();
		return;
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CTutorialBG::Draw(void)
{
	//�V�[��2D�̕`�揈���֐��Ăяo��
	CScene2d::Draw();
}
