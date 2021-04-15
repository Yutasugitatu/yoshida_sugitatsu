//******************************************************************************
// �_�C���̃p�[�e�B�N�� [dust_particle.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _DIA_PARTICLE_H_
#define _DIA_PARTICLE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "particle.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CDia_Particle : public CParticle
{
public:
	CDia_Particle(int nPrirority = 0);
	~CDia_Particle();
	static CDia_Particle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void DiaEffect_Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_move;		// �ړ�
	int m_nLife;			// ���C�t
};
#endif