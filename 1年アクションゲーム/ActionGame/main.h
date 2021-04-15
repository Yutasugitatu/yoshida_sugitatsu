#pragma once
//=============================================================================
//
// DirectX���^���� [main.h]
// Author : hoge fuga
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "input.h"
#include "Input.h"
#include "xaudio2.h"
#include "stdio.h"
//=============================================================================
// ���C�u�����̃����N
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")//�V�X�e���������Ƃ��悤�ɕK�v
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v

//=============================================================================
// �}�N����`
//=============================================================================
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define NUM_VERTEX (4)//���_��
#define NUM_POLYGON (2)//�|���S����
//=============================================================================
//�\���̒�`
//=============================================================================
//���[�h�̎��
typedef enum
{
	MODE_TITLE = 0,
	MODE_TITLE2,
	MODE_GAME,
	MODE_RESULT,
	MODE_GOAL,
	MODE_MAX
}MODE;
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p�W��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;
}VERTEX_2D;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);


#endif


