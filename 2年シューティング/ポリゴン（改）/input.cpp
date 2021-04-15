//-----------------------------------------------
//
//  入力処理[input.cpp]
//  author:杉立悠太
//
//-----------------------------------------------
#include "main.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

CInput::CInput()
{

}

CInput::~CInput()
{
}

//=============================================================================
//キーボードの初期化
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}
	return S_OK;
}

//キーボードの終了処理
void CInput::Uninit(void)
{
	//入力デバイス（キーボードの開放）
	if (m_pDevice != NULL)
	{
		//キーボードのアクセス権を開放（入力制御終了）

		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	//directinoutオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

CInputKeyboard::CInputKeyboard()
{
	//キー情報のクリア
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	//zeromemory(アドレス,バイト数);↑同じ
}

CInputKeyboard::~CInputKeyboard()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//directinputオブジェクトを作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイスの解放
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定する
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得
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
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力情報
	int nCntKey;

	//デバイスからデータの取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]);
			//キープレス情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	//キーボードの更新処理
	else
	{
		//キーボードのアクセス権を取得
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
