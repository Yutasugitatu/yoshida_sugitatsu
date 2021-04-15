//******************************************************************************
// �X�^���G�t�F�N�g [stan_effect.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _STAN_EFFECT_H_
#define _STAN_EFFECT_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "effect.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CStan_Effect : public CEffect
{
public:
	CStan_Effect(int nPriority = 0);
	~CStan_Effect();
	static CStan_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CEffect::TEX_TYPE TexType, float fRadian, float fLength);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void StanEffect_Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, float fLength);
	void AllRelease(void);
private:
	D3DXVECTOR3 m_pos;
	float m_fRadian;		// �ʓx
	float m_fLength;		// ���a
	float m_fAngle;			// �p�x
};
#endif