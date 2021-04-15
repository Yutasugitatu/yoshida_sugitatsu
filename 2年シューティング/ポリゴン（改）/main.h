//=============================================================================
//
// ���C������ [main.h]
// Author : �����I��
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "windows.h"
#include "d3dx9.h"
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"
#include "xaudio2.h"
#define _USE_MATH_DEFINES
#include <math.h>
class CRenderer;//�O���錾
class CScene;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int GetFPS(void);


//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH (1280)    // �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)    // �E�C���h�E�̍���
#define NUM_VERTEX  4
#define NUM_POLYGON  2
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//#define DIRECTINPUT_VERSION (0x800)				//�x���Ώ��p
#define SERVER_PORT_NUM (12345)				//�ڑ���T�[�o�[�̐ڑ���|�[�g
#define LOCAL_IP_ADDRESS	"127.0.0.1"		//���[�J��IP�A�h���X
#define IP_ADDRESS			"52.185.162.69"	//IP�A�h���X
#define  MAX_SCORE (8)
#define  SCORE_SIZEX (200.0f/10.0f)
#define  SCORE_SIZEY (60.0f)
#define SIZE_HALF (2)
#define IP "13.78.48.186"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos; // ���_���W
	float rhw;   // ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;  // ���_�J���[
	D3DXVECTOR2 tex; // �e�N�X�`�����W
} VERTEX_2D;

#endif