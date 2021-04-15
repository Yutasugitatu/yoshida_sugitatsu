#pragma once
//====================================================================
//
// �|�؂̏��� (wood.h)
// Author : ��{��
//
//====================================================================
#ifndef _WOOD_H_
#define _WOOD_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "model_himiya.h"

//================================================
// �}�N����`
//================================================
#define COLLISION_SIZE_WOOD D3DXVECTOR3(200.0f, 100.0f, 200.0f)

//================================================
// �N���X�錾
//================================================

// UI�N���X
class CWood : public CModelHimiya
{
public:
	CWood(int nPriority = OBJTYPE_WOOD);
	~CWood();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CWood *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	bool							m_bHit;
	D3DXVECTOR3						m_rot;
};

#endif