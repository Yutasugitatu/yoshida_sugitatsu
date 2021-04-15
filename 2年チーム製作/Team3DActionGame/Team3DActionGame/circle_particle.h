//******************************************************************************
// �~�`�̃p�[�e�B�N�� [circle_particle.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _CIRCLE_PARTICLE_H_
#define _CIRCLE_PARTICLE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "particle.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CCircle_Particle : public CParticle
{
public:
	CCircle_Particle(int nPrirority = 0);
	~CCircle_Particle();
	static CCircle_Particle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Effect_Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_move;		// �ړ�
	float m_fMinColor;		//	�F�̌��Z�l
};
#endif