
#ifndef _INPUT_H_
#define _INPUT_H_
#define _CRT_SECURE_NO_WARNINGS_
#define NUM_KEY_MAX (256)//キーの最大数
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CInput
{
public:
	CInput();
virtual	~CInput();
virtual	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
virtual	void Uninit(void);
virtual	void Update(void) = 0;
virtual	bool GetKeyBoardPress(int nKey) = 0;
virtual	bool GetKeyBoardTrigger(int nKey) = 0;
virtual	bool GetKeyBoardRelease(int nkey) = 0;
protected:
		LPDIRECTINPUTDEVICE8 m_pDevice;
static	LPDIRECTINPUT8 m_pInput;
};

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyBoardPress(int nKey);
	bool GetKeyBoardTrigger(int nKey);
	bool GetKeyBoardRelease(int nKey);
private:

	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
};

#endif 