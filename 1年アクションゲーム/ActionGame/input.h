#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_
#define _CRT_SECURE_NO_WARNINGS_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitKeyBoard(HINSTANCE hIsutance, HWND hWnd);
void UninitKeyBoard(void);
void UpdateKeyBoard(void);

bool GetKeyBoardPress(int nKey);
bool GetKeyBoardTrigger(int nKey);
bool GetKeyBoardRelease(int nkey);
#endif