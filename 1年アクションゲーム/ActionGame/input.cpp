// auther:sugi

#include "main.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define NUM_KEY_MAX (256)//キーの最大数
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyBoard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];
BYTE g_aKeyStateRelease[NUM_KEY_MAX];
//=============================================================================
//キーボードの初期化
//=============================================================================
HRESULT InitKeyBoard(HINSTANCE hInstance, HWND hWnd)
{
	//directinputオブジェクトを作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイスの解放
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyBoard, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定する
	if (FAILED(g_pDevKeyBoard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyBoard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得
	g_pDevKeyBoard->Acquire();
	{
		return S_OK;
	}
}

//キーボードの更新処理
void UpdateKeyBoard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力情報
	int nCntKey;

	//デバイスからデータの取得
	if (SUCCEEDED(g_pDevKeyBoard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]);
			//キープレス情報を保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	//キーボードの更新処理
	else
	{
		//キーボードのアクセス権を取得
		g_pDevKeyBoard->Acquire();
	}
}
//キーボードのプレス状態を取得
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
//キーボードの終了処理
void UninitKeyBoard(void)
{
	//入力デバイス（キーボードの開放）
	if (g_pDevKeyBoard != NULL)
	{
		//キーボードのアクセス権を開放（入力制御終了）

		g_pDevKeyBoard->Unacquire();
		g_pDevKeyBoard->Release();
		g_pDevKeyBoard = NULL;
	}
	//directinoutオブジェクトの開放
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput != NULL;
	}
}
