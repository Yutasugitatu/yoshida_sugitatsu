#pragma once
//=============================================================================
//
//  [title.h]
// Author : 杉立悠太
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"
#include "scene.h"
#define _CRT_SECURE_NO_WARNINGS
#define TITLE_BG (3);
#define MAX_TITLE_LOGO (128)
#define TITLE_SIZE_X (600)
#define TITLE_SIZE_Y (200)
#define MAX_TYPE_TITLE (128)
//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CScene2d;
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();
	static CTitle *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static	void UnLoad(void);
	HRESULT Init(D3DXVECTOR3 pos, int nSizeX = 1280, int nSizeY = 720);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static	LPDIRECT3DTEXTURE9  m_pTexture;
	CScene2d *m_apScene2D;
	CScene2d *m_apTitle;
};


#endif
