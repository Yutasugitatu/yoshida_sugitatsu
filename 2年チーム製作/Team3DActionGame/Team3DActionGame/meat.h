#pragma once
//====================================================================
//
// ���̏��� (meat.h)
// Author : ��K������
//
//====================================================================
#ifndef _MEAT_H_
#define _MEAT_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "main.h"
#include "model_himiya.h"

//================================================
// �}�N����`
//================================================
#define COLLISION_SIZE_MEAT D3DXVECTOR3(200.0f, 200.0f, 200.0f)

//================================================
// �N���X�錾
//================================================

// UI�N���X
class CMeat : public CModelHimiya
{
public:
	CMeat(int nPriority = OBJTYPE_DEFAULT);
	~CMeat();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CMeat *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_rot;
};

#endif

