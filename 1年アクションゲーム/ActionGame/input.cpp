// auther:sugi

#include "main.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_KEY_MAX (256)//�L�[�̍ő吔
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyBoard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];
BYTE g_aKeyStateRelease[NUM_KEY_MAX];
//=============================================================================
//�L�[�{�[�h�̏�����
//=============================================================================
HRESULT InitKeyBoard(HINSTANCE hInstance, HWND hWnd)
{
	//directinput�I�u�W�F�N�g���쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̉��
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyBoard, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ肷��
	if (FAILED(g_pDevKeyBoard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyBoard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyBoard->Acquire();
	{
		return S_OK;
	}
}

//�L�[�{�[�h�̍X�V����
void UpdateKeyBoard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//�f�o�C�X����f�[�^�̎擾
	if (SUCCEEDED(g_pDevKeyBoard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]);
			//�L�[�v���X����ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	//�L�[�{�[�h�̍X�V����
	else
	{
		//�L�[�{�[�h�̃A�N�Z�X�����擾
		g_pDevKeyBoard->Acquire();
	}
}
//�L�[�{�[�h�̃v���X��Ԃ��擾
bool GetKeyBoardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80 ? true : false);
}
bool GetKeyBoardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80 ? true : false);
}
bool GetKeyBoardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey] & 0x80 ? true : false);
}
//�L�[�{�[�h�̏I������
void UninitKeyBoard(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�̊J���j
	if (g_pDevKeyBoard != NULL)
	{
		//�L�[�{�[�h�̃A�N�Z�X�����J���i���͐���I���j

		g_pDevKeyBoard->Unacquire();
		g_pDevKeyBoard->Release();
		g_pDevKeyBoard = NULL;
	}
	//directinout�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput != NULL;
	}
}
