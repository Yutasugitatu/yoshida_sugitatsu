#pragma once
#pragma once
//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 杉立悠太
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#define _CRT_SECURE_NO_WARNINGS_
#include "main.h"

//*****************************************************************************
// サウンドファイル
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
	SOUND_LABEL_DETH,		// 死んだとき
	SOUND_LABEL_EXPLOSION,			// ヒット音
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
	// パラメータ構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int m_nCntLoop;		// ループカウント
	} SOUNDPARAM;
	//*****************************************************************************
	// グローバル変数
	//*****************************************************************************
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif
