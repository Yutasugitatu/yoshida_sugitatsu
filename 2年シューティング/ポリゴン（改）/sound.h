#pragma once
#pragma once
//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �����I��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#define _CRT_SECURE_NO_WARNINGS_
#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************

class CSound
{
public:
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,
	SOUND_LABEL_PLANT,			// jump
	SOUND_LABEL_DETH,		// ���񂾂Ƃ�
	SOUND_LABEL_EXPLOSION,			// �q�b�g��
	SOUND_LABEL_FIRE,
	SOUND_LABEL_ENTER,
	SOUND_LABEL_MAX,
} SOUND_LABEL;
CSound::CSound();
CSound::~CSound(); 
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int m_nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;
	//*****************************************************************************
	// �O���[�o���ϐ�
	//*****************************************************************************
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


#endif
