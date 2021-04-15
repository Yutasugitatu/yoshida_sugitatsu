//-----------------------------------------------
//
//  ���͏���[input.cpp]
//  author:�����I��
//
//-----------------------------------------------
#include "main.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

CInput::CInput()
{

}

CInput::~CInput()
{
}

//=============================================================================
//�L�[�{�[�h�̏�����
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}
	return S_OK;
}

//�L�[�{�[�h�̏I������
void CInput::Uninit(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�̊J���j
	if (m_pDevice != NULL)
	{
		//�L�[�{�[�h�̃A�N�Z�X�����J���i���͐���I���j

		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	//directinout�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

CInputKeyboard::CInputKeyboard()
{
	//�L�[���̃N���A
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	//zeromemory(�A�h���X,�o�C�g��);������
}

CInputKeyboard::~CInputKeyboard()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//directinput�I�u�W�F�N�g���쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̉��
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ肷��
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	{
		return S_OK;
	}
	return E_NOTIMPL;
}

void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//�f�o�C�X����f�[�^�̎擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]);
			//�L�[�v���X����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	//�L�[�{�[�h�̍X�V����
	else
	{
		//�L�[�{�[�h�̃A�N�Z�X�����擾
		m_pDevice->Acquire();
	}
}

bool CInputKeyboard::GetKeyBoardPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80 ? true : false);
}

bool CInputKeyboard::GetKeyBoardTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80 ? true : false);
}

bool CInputKeyboard::GetKeyBoardRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80 ? true : false);
}
